#ifndef TEST_H
#define TEST_H

#include "scene.h"
#include <QtTest>

class Test : public QObject {
  Q_OBJECT
public:
  Test();
private Q_SLOTS:
  void findBallWallBrinkCollision();
  void findBallInWallCollision();
  void findBallBallBrinkCollision();
  void findBallInBallCollision();
  void fendOffTopWall();
  void fendOffFrontWall();
  void fendOffLeftWall();
  void resolveOppositeVelocityCollision();

private:
  Scene *scene;
};

#endif // TEST_H
