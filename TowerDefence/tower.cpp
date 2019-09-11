#include "tower.h"
#include <QGraphicsRectItem>
#include <QLineF>
#include <QPixmap>
#include <QPointF>
#include <QPolygonF>
#include <QTimer>
#include <QVector>
#include "bullet.h"
#include "game.h"

extern Game *game;

Tower::Tower(QGraphicsItem *parent) : QObject(), QGraphicsPixmapItem(parent) {
  setPixmap(QPixmap(":/images/cannontower.png"));

  // create points vector
  QVector<QPointF> points;
  points << QPointF(1, 0) << QPointF(2, 0) << QPointF(3, 1) << QPointF(3, 2)
         << QPointF(2, 3) << QPointF(1, 3) << QPointF(0, 2) << QPointF(0, 1);

  // scale polygon
  const size_t SCALE_FACTOR = 200;
  for (int i{0}, n = points.size(); i < n; i++) {
    points[i] *= SCALE_FACTOR;
  }

  // create a polygon from these points
  //  QPolygonF polygon(points);

  // attack area
  attack_area = new QGraphicsPolygonItem(QPolygonF(points), this);

  // move polygon to the center
  QPointF poly_center(1.5, 1.5);
  poly_center *= SCALE_FACTOR;
  poly_center = mapToScene(poly_center);
  QPointF tower_center(x() + 44, y() + 44);
  QLineF line(poly_center, tower_center);
  attack_area->setPos(x() + line.dx(), y() + line.dy());

  // connect a timer to attack target
  QTimer *timer = new QTimer();
  connect(timer, SIGNAL(timeout()), this, SLOT(attack_target()));
  timer->start(1000);
  attack_dest = QPointF(800, 0);
}

void Tower::attack_target() {
  Bullet *bullet = new Bullet();
  bullet->setPos(x() + 44, y() + 44);

  QLineF line(QPointF(x() + 44, y() + 44), attack_dest);
  double angle = -1 * line.angle();
  bullet->setRotation(angle);
  game->scene->addItem(bullet);
}
