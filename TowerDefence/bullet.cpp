#include "bullet.h"
#include <qmath.h>
#include <QPixmap>
#include <QTimer>
#include "game.h"
extern Game* game;

Bullet::Bullet(QGraphicsItem* parent) : QObject(), QGraphicsPixmapItem(parent) {
  // set graphics
  setPixmap(QPixmap(":/images/bullet.png").scaledToWidth(40));

  // connect a timer
  QTimer* move_timer = new QTimer(this);
  connect(move_timer, SIGNAL(timeout()), this, SLOT(move()));
  move_timer->start(50);
}

void Bullet::move() {
  const int STEP_SIZE = 30;
  double theta = rotation();

  double dy = STEP_SIZE * qSin(qDegreesToRadians(theta));
  double dx = STEP_SIZE * qCos(qDegreesToRadians(theta));

  setPos(x() + dx, y() + dy);
}
