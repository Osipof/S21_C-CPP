#include "mainwindow.h"

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  setFixedWidth(500);

  connect(ui->pushButton_0, SIGNAL(clicked()), this, SLOT(digitNumbers()));
  connect(ui->pushButton_1, SIGNAL(clicked()), this, SLOT(digitNumbers()));
  connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(digitNumbers()));
  connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(digitNumbers()));
  connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(digitNumbers()));
  connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(digitNumbers()));
  connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(digitNumbers()));
  connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(digitNumbers()));
  connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(digitNumbers()));
  connect(ui->pushButton_9, SIGNAL(clicked()), this, SLOT(digitNumbers()));
  connect(ui->pushButton_x, SIGNAL(clicked()), this, SLOT(digitNumbers()));
  connect(ui->pushButton_power, SIGNAL(clicked()), this, SLOT(digitNumbers()));

  connect(ui->pushButton_addition, SIGNAL(clicked()), this,
          SLOT(digitNumbers()));
  connect(ui->pushButton_subtraction, SIGNAL(clicked()), this,
          SLOT(digitNumbers()));
  connect(ui->pushButton_multiplication, SIGNAL(clicked()), this,
          SLOT(digitNumbers()));
  connect(ui->pushButton_division, SIGNAL(clicked()), this,
          SLOT(digitNumbers()));

  connect(ui->pushButton_openBracket, SIGNAL(clicked()), this,
          SLOT(digitNumbers()));
  connect(ui->pushButton_closeBracket, SIGNAL(clicked()), this,
          SLOT(digitNumbers()));

  connect(ui->pushButton_sin, SIGNAL(clicked()), this, SLOT(operations()));
  connect(ui->pushButton_cos, SIGNAL(clicked()), this, SLOT(operations()));
  connect(ui->pushButton_tan, SIGNAL(clicked()), this, SLOT(operations()));
  connect(ui->pushButton_acos, SIGNAL(clicked()), this, SLOT(operations()));
  connect(ui->pushButton_asin, SIGNAL(clicked()), this, SLOT(operations()));
  connect(ui->pushButton_atan, SIGNAL(clicked()), this, SLOT(operations()));
  connect(ui->pushButton_sqrt, SIGNAL(clicked()), this, SLOT(operations()));
  connect(ui->pushButton_ln, SIGNAL(clicked()), this, SLOT(operations()));
  connect(ui->pushButton_log, SIGNAL(clicked()), this, SLOT(operations()));
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::digitNumbers() {
  // Возвращает нажатую кнопку
  QPushButton *button = (QPushButton *)sender();
  // Передаем в resultShow новую строку
  ui->lineEdit_input->setText(ui->lineEdit_input->text() + button->text());
}

void MainWindow::on_pushButton_dot_clicked() {
  ui->lineEdit_input->setText(ui->lineEdit_input->text() + ".");
}

void MainWindow::operations() {
  QPushButton *button = (QPushButton *)sender();
  ui->lineEdit_input->setText(ui->lineEdit_input->text() + button->text() +
                              "(");
}

void MainWindow::on_pushButton_clear_clicked() {
  ui->lineEdit_input->setText("");
  ui->lineEdit_result->setText("");
  ui->widget->clearGraphs();
  ui->widget->replot();
}

void MainWindow::on_pushButton_modulus_clicked() {
  QPushButton *button = (QPushButton *)sender();
  ui->lineEdit_input->setText(ui->lineEdit_input->text() + button->text());
}

void MainWindow::on_pushButton_equal_clicked() {
  std::string expression = ui->lineEdit_input->text().toStdString();
  const char *str = expression.c_str();
  if (strlen(str)) {
    double x = ui->doubleSpinBox_x->value();
    double result = 0;
    if (processCalculation(str, x, &result)) {
      ui->lineEdit_result->setText("Error!");
    } else {
      QString finalResult = QString::number(result, 'g', 7);
      ui->lineEdit_result->setText(finalResult);
    }
  }
}

void MainWindow::on_pushButton_graphic_clicked() {
  int code = OK;
  double h = 0.0001;
  double xmin = ui->spinBox_xmin->value();
  double xmax = ui->spinBox_xmax->value();
  double ymin = ui->spinBox_ymin->value();
  double ymax = ui->spinBox_ymax->value();

  // Проверка на корректность границ
  ui->widget->clearGraphs();
  if (xmin >= xmax || ymin >= ymax) {
    ui->lineEdit_result->setText("Incorrect borders");
    ui->widget->replot();
  } else {
    std::string expression = ui->lineEdit_input->text().toStdString();
    const char *str = expression.c_str();
    char parseString[512] = "";
    removeSpacesFromStr(str, parseString);
    int len = strlen(parseString);
    double result = 0;
    char *reversePolishNotation = (char *)malloc(len * sizeof(char));
    if (len > 255 ||
        stringToReversePolishNotation(parseString, reversePolishNotation)) {
      ui->lineEdit_result->setText("Error!");
    } else {
      ui->widget->xAxis->setRange(xmin, xmax);
      ui->widget->yAxis->setRange(ymin, ymax);

      int N = (xmax - xmin) / h;
      QVector<double> x(N), y(N);

      double xValue = xmin;
      for (int i = 0; i < N;) {
        result = calculate(reversePolishNotation, xValue, &code);
        if (code) {
          ui->lineEdit_result->setText("Error!");
          break;
        }
        if (result <= ymin || result >= ymax) {
          xValue += h;
          x[i] = xValue;
          y[i++] = NAN;
        } else {
          x[i] = xValue;
          y[i++] = result;
          xValue += h;
        }
      }

      ui->widget->addGraph();
      if (!code) ui->widget->graph(0)->addData(x, y);
      x.clear();
      y.clear();
      ui->widget->replot();
    }
    free(reversePolishNotation);
  }
}

void MainWindow::on_checkBox_stateChanged(int arg1) {
  if (arg1) {
    setFixedHeight(488);
    setFixedWidth(1013);
  } else {
    setFixedHeight(488);
    setFixedWidth(500);
  }
}
