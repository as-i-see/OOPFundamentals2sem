#ifndef COLLISIONSMASTER_H
#define COLLISIONSMASTER_H

#include "cage.h"
#include <QObject>
#include <ball.h>
#include <vector>

class CollisionsMaster : public QObject {
  Q_OBJECT
public:
  CollisionsMaster(int);
  int handleCollisions(std::vector<Ball *> &);
  double R = 1.0;

private:
  std::vector<Ball *> balls;
  Cage *cage;
  std::vector<std::pair<int, int>> collisionsOccured();
  void resolveBallsCollision(int, int);
};

#endif // COLLISIONSMASTER_H
