#include "ball.h"

Ball::Ball(float radius) { this->radius = radius; }

void Ball::translate(const QVector3D &dt) { translationVec += dt; }

void Ball::setTranslation(const QVector3D &t) { translationVec = t; }

const QMatrix4x4 &Ball::toMatrix() {
  modelWorldMatrix.setToIdentity();
  modelWorldMatrix.translate(translationVec);
  return modelWorldMatrix;
}
