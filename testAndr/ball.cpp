#include "ball.h"
#include <QQuaternion>
#include <QVector3D>
#include <cmath>

#define PI 3.14159265

Ball::Ball(float radius) : radius(radius) {
  std::vector<QVector3D> pattern;
  for (int i = 0; i < 360; i += 10) {
    pattern.push_back(
        QVector3D(0, radius * cos(i * PI / 180), radius * sin(i * PI / 180)));
  }
  QQuaternion rotationQuat = QQuaternion::fromAxisAndAngle(0.0f, 1.0f, 0.0f, 1);
  for (int i = 0; i < 180; i += 1) {
    for (int j = 0; j < 36; j++) {
      this->dots.push_back(pattern[j]);
      pattern[j] = rotationQuat * pattern[j];
    }
  }
}
