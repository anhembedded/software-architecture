from ast import main

from PySide6.QtWidgets import QApplication, QWidget, QMainWindow, QPushButton


class myApp(QMainWindow):
    def __init__(self):
        super().__init__()
        self.setWindowTitle("MyApp")
        self.button = QPushButton("PressMe!!")
        self.setCentralWidget(self.button)
        self.button.setCheckable(True)

        self.button.clicked.connect(self.the_button_was_clicked)
        self.button.toggled.connect(self.the_button_was_toggled)

    def the_button_was_clicked(self):
        print("Clicked!!")

    def the_button_was_toggled(self, checked):
        print("Checked?", checked)
        if checked:
            self.button.setText("Checked!!")
        else:
            self.button.setText("PressMe!!")

mainApp = QApplication()

thisApp = myApp()
thisApp.show()

mainApp.exec()

