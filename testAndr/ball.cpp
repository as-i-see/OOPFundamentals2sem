#include "ball.h"
#include <cmath>

Ball::Ball(float radius) { this->radius = radius; }

void Ball::translate(const QVector3D &dt) { translationVec += dt; }

void Ball::setTranslation(const QVector3D &t) { translationVec = t; }

const QMatrix4x4 &Ball::toMatrix() {
  modelWorldMatrix.setToIdentity();
  modelWorldMatrix.translate(translationVec);
  return modelWorldMatrix;
}

void Ball::insertBall(float r, float p, std::vector<float> &vertices) {
  float theta1 = 0.0, theta2 = 0.0, theta3 = 0.0;
  float ex = 0.0f, ey = 0.0f, ez = 0.0f;
  float px = 0.0f, py = 0.0f, pz = 0.0f;
  float cx = 0, cy = 0, cz = 0;

  for (int i = 0; i < p / 2; ++i) {
    theta1 = i * (M_PI * 2) / p - M_PI_2;
    theta2 = (i + 1) * (M_PI * 2) / p - M_PI_2;

    for (int j = 0; j <= p; ++j) {
      theta3 = j * (M_PI * 2) / p;

      ex = cosf(theta2) * cosf(theta3);
      ey = sinf(theta2);
      ez = cosf(theta2) * sinf(theta3);
      px = cx + r * ex;
      py = cy + r * ey;
      pz = cz + r * ez;

      vertices.push_back(px);
      vertices.push_back(py);
      vertices.push_back(pz);
      vertices.push_back(ex);
      vertices.push_back(ey);
      vertices.push_back(ez);

      ex = cosf(theta1) * cosf(theta3);
      ey = sinf(theta1);
      ez = cosf(theta1) * sinf(theta3);
      px = cx + r * ex;
      py = cy + r * ey;
      pz = cz + r * ez;

      vertices.push_back(px);
      vertices.push_back(py);
      vertices.push_back(pz);
      vertices.push_back(ex);
      vertices.push_back(ey);
      vertices.push_back(ez);
    }
  }
}
