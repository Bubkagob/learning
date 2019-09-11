#include "mainwindow.h"
#include <QtWidgets>
#include "scribblearea.h"

MainWindow::MainWindow() {
  scribbleArea = new ScribbleArea;
  setCentralWidget(scribbleArea);
  createActions();
  createMenus();
  setWindowTitle(tr("Scribble"));
  resize(500, 500);
}

void MainWindow::closeEvent(QCloseEvent *event) {
  if (maybeSave()) {
    event->accept();

  } else {
    event->ignore();
  }
}

void MainWindow::open() {
  if (maybeSave()) {
    QString filename = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                    QDir::currentPath());
    if (!filename.isEmpty()) {
      scribbleArea->openImage(filename);
    }
  }
}

void MainWindow::save() {
  QAction *action = qobject_cast<QAction *>(sender());
  QByteArray fileFormat = action->data().toByteArray();
  saveFile(fileFormat);
}

void MainWindow::penColor() {
  QColor newColor = QColorDialog::getColor(scribbleArea->penColor());
  if (newColor.isValid()) {
    scribbleArea->setPenColor(newColor);
  }
}

void MainWindow::penWidth() {
  bool ok;
  int newWidth =
      QInputDialog::getInt(this, tr("Scribble"), tr("Select pen width: "),
                           scribbleArea->penWidth(), 1, 50, 1, &ok);
  if (ok) {
    scribbleArea->setPenWidth(newWidth);
  }
}

void MainWindow::about() {
  QMessageBox::about(this, tr("About Scribble"),
                     tr("<p> The <b>Scribble</b> example is awesome</p>"));
}

void MainWindow::createActions() {
  openAction = new QAction(tr("&Open"), this);
  openAction->setShortcuts(QKeySequence::Open);
  connect(openAction, SIGNAL(triggered()), this, SLOT(open()));
  foreach (QByteArray format, QImageWriter::supportedImageFormats()) {
    QString text = tr("%1...").arg(QString(format).toUpper());
    QAction *action = new QAction(text, this);
    action->setData(format);
    connect(action, SIGNAL(triggered()), this, SLOT(save()));
    saveAsActions.append(action);
  }

  printAction = new QAction(tr("&Print..."), this);
  connect(printAction, SIGNAL(triggered()), scribbleArea, SLOT(print()));
  exitAction = new QAction(tr("&Exit..."), this);
  exitAction->setShortcut(QKeySequence::Quit);
  connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));

  penColorAction = new QAction(tr("&Pen Color ..."), this);
  connect(penColorAction, SIGNAL(triggered()), this, SLOT(penColor()));

  penWidthAction = new QAction(tr("&Pen Width ..."), this);
  connect(penWidthAction, SIGNAL(triggered()), this, SLOT(penWidth()));

  clearScreenAction = new QAction(tr("&Clear Screen"), this);
  clearScreenAction->setShortcut(tr("Ctrl+L"));
  connect(clearScreenAction, SIGNAL(triggered()), scribbleArea,
          SLOT(clearImage()));

  aboutAction = new QAction(tr("&About ..."), this);
  connect(aboutAction, SIGNAL(triggered()), SLOT(about()));

  aboutQTAction = new QAction(tr("About &Qt ..."), this);
  connect(aboutQTAction, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
}

void MainWindow::createMenus() {
  saveAsMenu = new QMenu(tr("&Save as"), this);
  foreach (QAction *action, saveAsActions)
    saveAsMenu->addAction(action);

  fileMenu = new QMenu(tr("&File"), this);
  fileMenu->addAction(openAction);
  fileMenu->addMenu(saveAsMenu);

  fileMenu->addAction(printAction);
  fileMenu->addSeparator();
  fileMenu->addAction(exitAction);

  optionsMenu = new QMenu(tr("&Options"), this);
  optionsMenu->addAction(penColorAction);
  optionsMenu->addAction(penWidthAction);
  optionsMenu->addSeparator();
  optionsMenu->addAction(clearScreenAction);

  helpMenu = new QMenu(tr("&Help"), this);
  helpMenu->addAction(aboutAction);
  helpMenu->addAction(aboutQTAction);

  menuBar()->addMenu(fileMenu);
  menuBar()->addMenu(optionsMenu);
  menuBar()->addMenu(helpMenu);
}

bool MainWindow::maybeSave() {
  if (scribbleArea->isModified()) {
    QMessageBox::StandardButton ret;
    ret = QMessageBox::warning(
        this, tr("Scribble"),
        tr("The image has been modified.\n"
           "Do you want to save your changes?"),
        QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
    if (ret == QMessageBox::Save) {
      return saveFile("png");

    } else if (ret == QMessageBox::Cancel) {
      return false;
    }
  }
  return true;
}

bool MainWindow::saveFile(const QByteArray &fileFormat) {
  QString initialPath = QDir::currentPath() + "/untitled." + fileFormat;
  QString fileName = QFileDialog::getSaveFileName(
      this, tr("Save As"), initialPath,
      tr("%1 Files(*.%2);; All Files(*")
          .arg(QString::fromLatin1(fileFormat.toUpper()))
          .arg(QString::fromLatin1(fileFormat)));

  if (fileName.isEmpty()) {
    return false;

  } else {
    return scribbleArea->saveImage(fileName, fileFormat.constData());
  }
}
