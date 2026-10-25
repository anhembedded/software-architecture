from PySide6.QtWidgets import QApplication, QWidget, QMainWindow

class MyApp(QMainWindow):
    def __init__(self):
        super().__init__()
        self.setWindowTitle("UI Window")
        self.setFixedSize(800,600)


app = QApplication()
Window = MyApp()
Window.show()
app.exec()
