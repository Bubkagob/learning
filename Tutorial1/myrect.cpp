#include "myrect.h"
#include <QDebug>
#include <QGraphicsScene>
#include <QKeyEvent>
#include "bullet.h"
void MyRect::keyPressEvent(QKeyEvent *event) {
  if (event->key() == Qt::Key_Left) {
    setPos(x() - 10, y());
  } else if (event->key() == Qt::Key_Right) {
    setPos(x() + 10, y());
  } else if (event->key() == Qt::Key_Up) {
    setPos(x(), y() - 10);
  } else if (event->key() == Qt::Key_Down) {
    setPos(x(), y() + 10);
  } else if (event->key() == Qt::Key_Space) {
    // create a bullet
    Bullet *bullet = new Bullet();
    qDebug() << "Bullet created";

    bullet->setPos(x(), y());
    scene()->addItem(bullet);
  }
}
