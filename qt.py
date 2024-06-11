from PySide6.QtWidgets import QApplication, QMainWindow, QVBoxLayout, QWidget, QPushButton, QHBoxLayout, QLineEdit, QLabel, QFileDialog, QComboBox
from pyqtgraph import PlotWidget, plot
import pyqtgraph as pg
import sys
from PySide6.QtCore import Qt
from PySide6.QtGui import QPen

class MainWindow(QMainWindow):

    def __init__(self):
        super().__init__()
        self.setWindowTitle("Graph Plotter")

        # Создаем ручки для графика
        self.plot_pen = pg.mkPen(color=(255, 0, 0), width=2)
        self.axis_pen = pg.mkPen(color=(0, 0, 0), width=1)

        # Создаем виджет для графика
        self.graphWidget = pg.PlotWidget()
        self.graphWidget.setBackground((211, 211, 211))

        # Начальные данные для графика: x и y с нулевыми значениями
        self.plot_data([0, 0], [0, 0])

        # Кнопка построения графика
        plot_button = QPushButton("Plot")
        plot_button.clicked.connect(self.plot_graph)

        # Кнопка сохранения графика
        save_button = QPushButton("Save Graph")
        save_button.clicked.connect(self.save_graph)

        # Метки и поля ввода для коэффициента наклона и пересечения с осью Y
        slope_label = QLabel("Введите наклон")
        self.slope_input = QLineEdit()
        intercept_label = QLabel("Введите пересечения с осью Y")
        self.intercept_input = QLineEdit()

        # Выпадающий список для выбора типа графика
        self.graph_type = QComboBox()
        self.graph_type.addItem("Linear")
        self.graph_type.addItem("Quadratic")

        # Макет для полей ввода и меток
        input_layout = QHBoxLayout()
        input_layout.addWidget(slope_label)
        input_layout.addWidget(self.slope_input)
        input_layout.addWidget(intercept_label)
        input_layout.addWidget(self.intercept_input)
        input_layout.addWidget(self.graph_type)

        # Основной макет для виджетов
        layout = QVBoxLayout()
        layout.addLayout(input_layout)
        layout.addWidget(plot_button)
        layout.addWidget(save_button)
        layout.addWidget(self.graphWidget)

        # Создаем основной виджет и устанавливаем макет
        widget = QWidget()
        widget.setLayout(layout)
        self.setCentralWidget(widget)

    def plot_data(self, x, y):
        """Функция для построения данных на графике."""
        self.graphWidget.clear()

        # Построение осей X и Y
        self.graphWidget.plot([-200, 200], [0, 0], pen=self.axis_pen)  # ось X
        self.graphWidget.plot([0, 0], [-200, 200], pen=self.axis_pen)  # ось Y

        # Построение данных
        self.graphWidget.plot(x, y, pen=self.plot_pen)
        self.graphWidget.setBackground('w')
        self.graphWidget.setLabel('left', 'Y-Axis')
        self.graphWidget.setLabel('bottom', 'X-Axis')

    # Слот для обработки нажатия кнопки построения графика
    def plot_graph(self):
        # Получаем текст из полей ввода
        slope_text = self.slope_input.text()
        intercept_text = self.intercept_input.text()

        # Преобразуем текст в числа, если текст пуст, то значение будет 0
        slope = float(slope_text) if slope_text else 0
        intercept = float(intercept_text) if intercept_text else 0

        # Выбор типа графика
        graph_type = self.graph_type.currentText()

        # Данные для построения графика
        x = list(range(-100, 101))
        if graph_type == "Linear":
            y = [i * slope + intercept for i in x]
        elif graph_type == "Quadratic":
            y = [i**2 * slope + intercept for i in x]

        # Построение данных
        self.plot_data(x, y)

    # Слот для сохранения графика
    def save_graph(self):
        # Открываем диалог сохранения файла
        file_name, _ = QFileDialog.getSaveFileName(self, "Save Graph", "", "PNG Files (*.png);;All Files (*)")
        if file_name:
            # Захват изображения виджета графика
            pixmap = self.graphWidget.grab()
            pixmap.save(file_name)

# Запуск приложения
if __name__ == "__main__":
    app = QApplication([])
