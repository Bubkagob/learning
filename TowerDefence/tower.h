#ifndef TOWER_H
#define TOWER_H
#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QGraphicsPolygonItem>
#include <QObject>
#include <QPointF>

class Tower : public QObject, public QGraphicsPixmapItem {
  Q_OBJECT

 public:
  Tower(QGraphicsItem* parent = nullptr);

 public slots:
  void attack_target();

 private:
  QGraphicsPolygonItem* attack_area;
  QPointF attack_dest;
};

#endif  // TOWER_H
