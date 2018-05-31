#ifndef BALL_H
#define BALL_H

#include <QObject>
#include <transform3d.h>
#include <vector>

class Ball {
public:
  Ball(float);
  Transform3D transform;
  QVector3D direction;
  float radius;
  QVector3D color;
};

#endif // BALL_H
