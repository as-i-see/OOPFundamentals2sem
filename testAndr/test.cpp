#include "test.h"
#include "ball.h"
#include "scene.h"
#include <QDebug>

Test::Test() {
  scene = new Scene;
  scene->createBallObjects();
}

void Test::findBallWallBrinkCollision() {
  scene->genStartUp();
  scene->balls[0]->transform.setTranslation(42, 0, 0);
  auto collisions = scene->collisionsOccured();
  QCOMPARE(collisions.size(), 1);
}

void Test::findBallInWallCollision() {
  scene->genStartUp();
  scene->balls[0]->transform.setTranslation(43, 0, 0);
  auto collisions = scene->collisionsOccured();
  QCOMPARE(collisions.size(), 1);
}

void Test::findBallBallBrinkCollision() {
  scene->genStartUp();
  scene->balls[1]->transform.setTranslation(-12, -20, 0);
  scene->balls[2]->transform.setTranslation(16, -20, 0);
  auto collisions = scene->collisionsOccured();
  QCOMPARE(collisions.size(), 1);
}

void Test::findBallInBallCollision() {
  scene->genStartUp();
  scene->balls[1]->transform.setTranslation(-11.5, -20, 0);
  scene->balls[2]->transform.setTranslation(15.5, -20, 0);
  auto collisions = scene->collisionsOccured();
  QCOMPARE(collisions.size(), 1);
}

void Test::fendOffTopWall() {
  scene->genStartUp();
  QVector3D initialVelocity = scene->balls[0]->direction;
  scene->balls[0]->transform.setTranslation(0, 42, 0);
  scene->handleCollisions();
  QVERIFY(initialVelocity.y() == -1 * scene->balls[0]->direction.y());
}

void Test::fendOffFrontWall() {
  scene->genStartUp();
  QVector3D initialVelocity = scene->balls[0]->direction;
  scene->balls[0]->transform.setTranslation(0, 0, -42);
  scene->handleCollisions();
  QVERIFY(initialVelocity.z() == -1 * scene->balls[0]->direction.z());
}

void Test::fendOffLeftWall() {
  scene->genStartUp();
  QVector3D initialVelocity = scene->balls[0]->direction;
  scene->balls[0]->transform.setTranslation(-42, 0, 0);
  scene->handleCollisions();
  QVERIFY(initialVelocity.x() == -1 * scene->balls[0]->direction.x());
}

void Test::resolveOppositeVelocityCollision() {
  scene->genStartUp();
  scene->balls[1]->transform.setTranslation(-12, -20, 0);
  scene->balls[1]->direction = QVector3D(1.0f, 0.0f, 0.0f);
  scene->balls[2]->transform.setTranslation(16, -20, 0);
  scene->balls[2]->direction = QVector3D(-1.0f, 0.0f, 0.0f);
  scene->resolveBallsCollision(7, 8);
  QVERIFY(scene->balls[1]->direction.x() < 0);
  QVERIFY(scene->balls[1]->direction.y() == 0);
  QVERIFY(scene->balls[1]->direction.z() == 0);
  QVERIFY(scene->balls[2]->direction.x() > 0);
  QVERIFY(scene->balls[2]->direction.y() == 0);
  QVERIFY(scene->balls[2]->direction.z() == 0);
}
