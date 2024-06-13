from PySide6.QtWidgets import QApplication, QMainWindow, QVBoxLayout, QWidget, QPushButton, QHBoxLayout, QLineEdit, QLabel, QFileDialog, QComboBox
from pyqtgraph import PlotWidget, plot
import pyqtgraph as pg
import sys
from PySide6.QtCore import Qt
from PySide6.QtGui import QPen


class MainWindow(QMainWindow): # Создаем класс MainWindow, который наследуется от класса QMainWindow

    def __init__(self): # Создание конструктора
        super().__init__() # Вызов конструктора родительского класса, что позволяет наследовать его инициализацию
        self.setWindowTitle("Graph Plotter")

        self.plot_pen = pg.mkPen(color=(255, 0, 0), width=2) # Создание объекта QPen функцией mkPen()
        self.axis_pen = pg.mkPen(color=(0, 0, 0), width=1) # Создание объекта QPen функцией mkPen()

        self.graphWidget = pg.PlotWidget() # Создаем экземпляр PlotWidget
        self.graphWidget.setBackground((211, 211, 211))

        self.plot_data([0, 0], [0, 0]) # Начальные значения для графика

        plot_button = QPushButton("Plot") # Создаем экземпляр кнопки
        plot_button.clicked.connect(self.plot_graph) # Привязывает метод self.plot_graph к событию нажатия на кнопку plot_button

        save_button = QPushButton("Save Graph")
        save_button.clicked.connect(self.save_graph)

        slope_label = QLabel("Введите наклон") # Создаем объект класса QLabel, который будет отображать текст
        self.slope_input = QLineEdit() # Создает поле ввода

        intercept_label = QLabel("Введите пересечения с осью Y") # Создает объект класса QLabel, который будет отображать текст
        self.intercept_input = QLineEdit()

        self.graph_type = QComboBox() # Создаем объект выпадающего списка
        self.graph_type.addItem("Linear") # Добавляем элемент
        self.graph_type.addItem("Quadratic") # Добавляем элемент

        input_layout = QHBoxLayout() # Создаем горизонтальный экземпляр виджета
        input_layout.addWidget(slope_label) # Добавляем метку "Введите наклон" (slope_label) в горизонтальный макет input_layout
        input_layout.addWidget(self.slope_input) # Добавляем поле ввода (self.slope_input) в горизонтальный макет input_layout
        input_layout.addWidget(intercept_label) # Добавляем метку "Введите пересечение с осью Y" (intercept_label) в горизонтальный макет input_layout
        input_layout.addWidget(self.intercept_input) # Добавляем поле ввода (self.intercept_input) в горизонтальный макет input_layout
        input_layout.addWidget(self.graph_type) # Добавляем выпадающий список (self.graph_type) в горизонтальный макет input_layout

        layout = QVBoxLayout() # Создаем вертикальный экземпляр виджета
        layout.addLayout(input_layout) # Добавляем горизонтальный макет input_layout в вертикальный макет layout
        layout.addWidget(plot_button) # Добавляем кнопку "Plot" (plot_button) в вертикальный макет layout
        layout.addWidget(save_button) # Добавляем кнопку "Save Graph" (save_button) в вертикальный макет layout
        layout.addWidget(self.graphWidget) # Добавляем виджет для графика (self.graphWidget) в вертикальный макет layout

        widget = QWidget()
        widget.setLayout(layout) # Устанавливаем вертикальный макет layout в качестве макета для основного виджета widget
        self.setCentralWidget(widget) # Устанавливаем основной виджет widget в качестве центрального виджета главного окна

    def plot_data(self, x, y):
        self.graphWidget.clear()

        self.graphWidget.plot([-200, 200], [0, 0], pen=self.axis_pen)  # ось X
        self.graphWidget.plot([0, 0], [-200, 200], pen=self.axis_pen)  # ось Y

        self.graphWidget.plot(x, y, pen=self.plot_pen)
        self.graphWidget.setBackground('w')
        self.graphWidget.setLabel('left', 'Y-Axis')
        self.graphWidget.setLabel('bottom', 'X-Axis')

    def plot_graph(self):
        # Получаем текст из полей ввода
        slope_text = self.slope_input.text()
        intercept_text = self.intercept_input.text()

        slope = float(slope_text) if slope_text else 0
        intercept = float(intercept_text) if intercept_text else 0

        # Выбор типа графика
        graph_type = self.graph_type.currentText()

        x = list(range(-100, 101))
        if graph_type == "Linear":
            y = [i * slope + intercept for i in x]
        elif graph_type == "Quadratic":
            y = [i**2 * slope + intercept for i in x]

        # Построение данных
        self.plot_data(x, y)

    # Слот для сохранения графика
    def save_graph(self):
        file_name, _ = QFileDialog.getSaveFileName(self, "Save Graph", "", "PNG Files (*.png);;All Files (*)") # второе значение не используется и его можно проигнорировать
        if file_name:
            # Захват изображения виджета графика
            pixmap = self.graphWidget.grab()
            pixmap.save(file_name)

if __name__ == "__main__": # условие проверяет, запущен ли данный скрипт напрямую (как основная программа), а не импортирован ли он как модуль в другом скрипте
    app = QApplication([]) # Создаем объект приложения QApplication. QApplication представляет собой основу для всех интерфейсов Qt-приложений
    main_window = MainWindow() # Создаем экземпляр класса MainWindow
    main_window.resize(800, 600)
    main_window.show() # метод для отображения главного окна

    sys.exit(app.exec()) # Метод app.exec() запускает бесконечный цикл обработки событий Qt. 
