#include "game.h"
#include <QGraphicsScene>
#include "bullet.h"
#include "tower.h"

Game::Game() : QGraphicsView() {
  // Create a scene
  scene = new QGraphicsScene(this);
  scene->setSceneRect(0, 0, 1000, 900);

  // set the scene
  setScene(scene);

  // create A tower
  Tower* t = new Tower();
  t->setPos(250, 250);
  // add tower to the scene

  scene->addItem(t);

  setFixedSize(1000, 900);
  setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

void Game::mousePressEvent(QMouseEvent* event) {
  Bullet* bullet = new Bullet();
  bullet->setPos(event->pos());
  bullet->setRotation(40);
  scene->addItem(bullet);
}
