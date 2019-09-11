#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_actionNew_triggered() {
  currentFile.clear();
  ui->myTextEdit->setText(QString());
}

void MainWindow::on_actionOpen_triggered() {
  QString fileName = QFileDialog::getOpenFileName(this, "Open the file");
  QFile file(fileName);
  currentFile = fileName;
  if (!file.open(QIODevice::ReadOnly | QFile::Text)) {
    QMessageBox::warning(this, "Warning",
                         "Cannot open file : " + file.errorString());
  }
  setWindowTitle(fileName);
  QTextStream in(&file);
  QString text = in.readAll();
  ui->myTextEdit->setText(text);
  file.close();
}

void MainWindow::on_actionSave_as_triggered() {
  QString fileName = QFileDialog::getSaveFileName(this, "Save as");
  QFile file(fileName);
  if (!file.open(QFile::WriteOnly | QFile::Text)) {
    QMessageBox::warning(this, "Warning",
                         "Cannot save file : " + file.errorString());
  }

  currentFile = fileName;
  setWindowTitle(fileName);
  QTextStream out(&file);
  QString text = ui->myTextEdit->toPlainText();
  out << text;
  file.close();
}

void MainWindow::on_actionPrint_triggered() {
  QPrinter printer;
  printer.setPrinterName("Printer Name");
  QPrintDialog pDialog(&printer, this);
  if (pDialog.exec() == QDialog::Rejected) {
    QMessageBox::warning(this, "Warning", "Cannot access printer");
    return;
  }
  ui->myTextEdit->print(&printer);
}

void MainWindow::on_actionExit_triggered() { QApplication::quit(); }

void MainWindow::on_actionCopy_triggered() { ui->myTextEdit->copy(); }

void MainWindow::on_actionPaste_triggered() { ui->myTextEdit->paste(); }
