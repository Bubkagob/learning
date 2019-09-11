#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class Calculator;
}

class Calculator : public QMainWindow {
  Q_OBJECT

 public:
  explicit Calculator(QWidget *parent = nullptr);
  ~Calculator();

 private:
  Ui::Calculator *ui;
 private slots:
  void NumPressed();
  void MathButtonPressed();
  void EqualButton();
  void ChangeNumberSign();
};

#endif  // MAINWINDOW_H
