import json
import sys

from PySide6 import QtCore, QtGui, QtWidgets
from PySide6.QtCore import Qt
from PySide6.QtUiTools import loadUiType


qt_creator_file = "mainwindow.ui"
Ui_MainWindow, QtBaseClass = loadUiType(qt_creator_file)
tick = QtGui.QImage("tick.png")


class TodoModel(QtCore.QAbstractListModel):
    def __init__(self, *args, todos=None, **kwargs):
        super().__init__(*args, **kwargs)
        self.todos = todos or []
        self.filter_mode = "All"
        self.search_text = ""
        self.visible_rows = []
        self.refresh()

    def data(self, index, role):
        if not index.isValid():
            return None

        source_row = self.visible_rows[index.row()]
        todo = self.todos[source_row]

        if role == Qt.DisplayRole:
            return todo["text"]

        if role == Qt.DecorationRole and todo["done"]:
            return tick

        if role == Qt.FontRole and todo["done"]:
            font = QtGui.QFont()
            font.setStrikeOut(True)
            return font

        if role == Qt.ForegroundRole and todo["done"]:
            return QtGui.QColor("#6b7280")

        return None

    def rowCount(self, index):
        if index.isValid():
            return 0
        return len(self.visible_rows)

    def refresh(self):
        self.visible_rows = [
            row for row, todo in enumerate(self.todos) if self.matches_filter(todo)
        ]
        self.layoutChanged.emit()

    def matches_filter(self, todo):
        search_text = self.search_text.lower()
        text_matches = search_text in todo["text"].lower()

        if self.filter_mode == "Active":
            return not todo["done"] and text_matches
        if self.filter_mode == "Completed":
            return todo["done"] and text_matches
        return text_matches

    def set_filter_mode(self, filter_mode):
        self.filter_mode = filter_mode
        self.refresh()

    def set_search_text(self, text):
        self.search_text = text.strip()
        self.refresh()

    def map_to_source_row(self, proxy_row):
        return self.visible_rows[proxy_row]


class MainWindow(QtWidgets.QMainWindow, Ui_MainWindow):
    def __init__(self):
        QtWidgets.QMainWindow.__init__(self)
        Ui_MainWindow.__init__(self)
        self.setupUi(self)

        self.model = TodoModel()
        self.load()
        self.todoView.setModel(self.model)
        self.todoView.doubleClicked.connect(self.toggle_complete)

        self.todoEdit.setPlaceholderText("Add a new task...")
        self.todoEdit.returnPressed.connect(self.add)

        self.add_extra_controls()
        self.bind_events()
        self.update_status()

    def add_extra_controls(self):
        self.filterCombo = QtWidgets.QComboBox()
        self.filterCombo.addItems(["All", "Active", "Completed"])

        self.searchEdit = QtWidgets.QLineEdit()
        self.searchEdit.setPlaceholderText("Search tasks...")
        self.searchEdit.setClearButtonEnabled(True)
        self.searchEdit.setMaximumWidth(180)

        self.editButton = QtWidgets.QPushButton("Edit")
        self.clearCompletedButton = QtWidgets.QPushButton("Clear Completed")

        self.horizontalLayout.addWidget(self.editButton)
        self.verticalLayout.insertWidget(2, self.filterCombo)
        self.verticalLayout.insertWidget(3, self.searchEdit)
        self.verticalLayout.insertWidget(5, self.clearCompletedButton)

    def bind_events(self):
        self.addButton.pressed.connect(self.add)
        self.deleteButton.pressed.connect(self.delete)
        self.completeButton.pressed.connect(self.toggle_complete)
        self.editButton.pressed.connect(self.edit)
        self.clearCompletedButton.pressed.connect(self.clear_completed)
        self.filterCombo.currentTextChanged.connect(self.apply_filter)
        self.searchEdit.textChanged.connect(self.apply_search)

    def add(self):
        text = self.todoEdit.text().strip()
        if not text:
            self.statusbar.showMessage("Enter a task before adding.", 2000)
            return

        self.model.todos.append({"done": False, "text": text})
        self.todoEdit.clear()
        self.model.refresh()
        self.save()
        self.update_status("Task added.")

    def delete(self):
        source_row = self.get_selected_source_row()
        if source_row is None:
            self.statusbar.showMessage("Select a task to delete.", 2000)
            return

        del self.model.todos[source_row]
        self.todoView.clearSelection()
        self.model.refresh()
        self.save()
        self.update_status("Task deleted.")

    def toggle_complete(self, index=None):
        source_row = self.get_selected_source_row()
        if source_row is None:
            self.statusbar.showMessage("Select a task to update.", 2000)
            return

        todo = self.model.todos[source_row]
        todo["done"] = not todo["done"]
        self.todoView.clearSelection()
        self.model.refresh()
        self.save()

        message = "Task completed." if todo["done"] else "Task marked active."
        self.update_status(message)

    def edit(self):
        source_row = self.get_selected_source_row()
        if source_row is None:
            self.statusbar.showMessage("Select a task to edit.", 2000)
            return

        todo = self.model.todos[source_row]
        text, accepted = QtWidgets.QInputDialog.getText(
            self,
            "Edit task",
            "Task:",
            text=todo["text"],
        )

        if not accepted:
            return

        updated_text = text.strip()
        if not updated_text:
            self.statusbar.showMessage("Task text cannot be empty.", 2000)
            return

        todo["text"] = updated_text
        self.model.refresh()
        self.save()
        self.update_status("Task updated.")

    def clear_completed(self):
        completed_count = sum(1 for todo in self.model.todos if todo["done"])
        if not completed_count:
            self.statusbar.showMessage("There are no completed tasks to clear.", 2000)
            return

        self.model.todos = [todo for todo in self.model.todos if not todo["done"]]
        self.todoView.clearSelection()
        self.model.refresh()
        self.save()
        self.update_status(f"Removed {completed_count} completed task(s).")

    def apply_filter(self, filter_mode):
        self.model.set_filter_mode(filter_mode)
        self.update_status()

    def apply_search(self, text):
        self.model.set_search_text(text)
        self.update_status()

    def get_selected_source_row(self):
        indexes = self.todoView.selectedIndexes()
        if not indexes:
            return None
        return self.model.map_to_source_row(indexes[0].row())

    def load(self):
        try:
            with open("data.db", "r", encoding="utf-8") as file_handle:
                raw_todos = json.load(file_handle)
        except Exception:
            raw_todos = []

        self.model.todos = [self.normalize_todo(todo) for todo in raw_todos]
        self.model.refresh()

    def normalize_todo(self, todo):
        if isinstance(todo, dict):
            return {
                "done": bool(todo.get("done", False)),
                "text": str(todo.get("text", "")).strip(),
            }

        if isinstance(todo, (list, tuple)) and len(todo) >= 2:
            return {"done": bool(todo[0]), "text": str(todo[1]).strip()}

        return {"done": False, "text": str(todo).strip()}

    def save(self):
        with open("data.db", "w", encoding="utf-8") as file_handle:
            json.dump(self.model.todos, file_handle, indent=2)

    def update_status(self, message=None):
        total = len(self.model.todos)
        completed = sum(1 for todo in self.model.todos if todo["done"])
        active = total - completed
        visible = len(self.model.visible_rows)

        summary = (
            f"Total: {total} | Active: {active} | Completed: {completed} | Visible: {visible}"
        )

        if message:
            self.statusbar.showMessage(f"{message}  {summary}", 4000)
        else:
            self.statusbar.showMessage(summary)


app = QtWidgets.QApplication(sys.argv)
window = MainWindow()
window.show()
app.exec()
