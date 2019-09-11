#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QList>
#include <QMainWindow>

class ScribbleArea;

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow();

 protected:
  void closeEvent(QCloseEvent *event) override;

 private slots:
  void open();
  void save();
  void penColor();
  void penWidth();
  void about();

 private:
  void createActions();
  void createMenus();
  bool maybeSave();
  bool saveFile(const QByteArray &fileFormat);
  ScribbleArea *scribbleArea;
  QMenu *saveAsMenu;
  QMenu *fileMenu;
  QMenu *optionsMenu;
  QMenu *helpMenu;
  QAction *openAction;
  QList<QAction *> saveAsActions;
  QAction *penColorAction;
  QAction *penWidthAction;
  QAction *printAction;
  QAction *exitAction;
  QAction *clearScreenAction;
  QAction *aboutAction;
  QAction *aboutQTAction;
};
#endif  // MAINWINDOW_H
