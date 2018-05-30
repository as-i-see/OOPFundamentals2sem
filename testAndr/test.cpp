#include "test.h"
#include "ball.h"
#include "scene.h"
#include <QDebug>

Test::Test() {
  scene = new Scene;
  scene->createBallObjects();
}

void Test::oppositeVelocityCollision() {
  scene->balls[0]->transform.setTranslation(8, 0, 0);
  scene->balls[0]->direction = QVector3D(-1, 0, 0);
  scene->balls[1]->transform.setTranslation(-12, 0, 0);
  scene->balls[1]->direction = QVector3D(1, 0, 0);
  scene->balls[2]->transform.setTranslation(30, 30, 30);
  scene->balls[2]->direction = QVector3D(1, 0, 0);
  scene->handleCollisions();
  QCOMPARE(scene->balls[0]->direction, QVector3D(1, 0, 0));
  QCOMPARE(scene->balls[1]->direction, QVector3D(-1, 0, 0));
}
