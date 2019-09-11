#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QFile>
#include <QFileDialog>
#include <QMainWindow>
#include <QMessageBox>
#include <QPrintDialog>
#include <QPrinter>
#include <QTextStream>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  explicit MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private slots:
  void on_actionNew_triggered();

  void on_actionOpen_triggered();

  void on_actionSave_as_triggered();

  void on_actionPrint_triggered();

  void on_actionExit_triggered();

  void on_actionCopy_triggered();

  void on_actionPaste_triggered();

 private:
  Ui::MainWindow *ui;
  QString currentFile = "";
};

#endif  // MAINWINDOW_H
