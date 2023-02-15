#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <math.h>

#include <QMainWindow>
#include <QVector>

#ifdef __cplusplus
extern "C"
{
#endif

#include "../polishNotation.h"

#ifdef __cplusplus
}
#endif

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private:
  Ui::MainWindow *ui;

 private slots:
  void digitNumbers();
  void on_pushButton_dot_clicked();
  void operations();
  void on_pushButton_clear_clicked();
  void on_pushButton_modulus_clicked();
  void on_pushButton_equal_clicked();
  void on_pushButton_graphic_clicked();
  void on_checkBox_stateChanged(int arg1);
};
#endif  // MAINWINDOW_H
