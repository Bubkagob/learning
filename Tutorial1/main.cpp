#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include "myrect.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);

  // Create a scene

  QGraphicsScene *scene = new QGraphicsScene();

  // Create an item to put into the scene
  MyRect *rect = new MyRect();
  rect->setRect(0, 0, 100, 100);

  // Add the rect to the scene
  scene->addItem(rect);

  // 1. make rectangle focusable
  rect->setFlag(QGraphicsItem::ItemIsFocusable);
  rect->setFocus();

  // Add a view
  QGraphicsView *view = new QGraphicsView(scene);
  // view -> setScene(scene);
  view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  view->show();

  return a.exec();
}
