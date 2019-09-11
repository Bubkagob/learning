#include "calculator.h"
#include "ui_mainwindow.h"

double defaultValue = 0.0;
bool divTrigger = false;
bool multTrigger = false;
bool addTrigger = false;
bool subTrigger = false;

Calculator::Calculator(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::Calculator) {
  ui->setupUi(this);
  ui->Display->setText(QString::number(defaultValue));
  QPushButton *numButtons[10];
  for (int i = 0; i < 10; i++) {
    QString butName = "Button" + QString::number(i);
    numButtons[i] = Calculator::findChild<QPushButton *>(butName);
  }
}

Calculator::~Calculator() { delete ui; }
