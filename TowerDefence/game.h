#ifndef GAME_H
#define GAME_H
#include <QGraphicsView>
#include <QMouseEvent>

class Game : public QGraphicsView {
 public:
  Game();

  void mousePressEvent(QMouseEvent* event);
  // member attributes
  QGraphicsScene* scene;
};

#endif  // GAME_H
