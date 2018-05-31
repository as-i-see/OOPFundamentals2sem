#ifndef BALL_H
#define BALL_H

#include <QMatrix4x4>
#include <QObject>
#include <QVector3D>
#include <vector>

class Ball {
public:
  Ball(float);
  QVector3D direction;
  float radius;
  QVector3D color;
  void translate(const QVector3D &dt);
  void translate(float dx, float dy, float dz);
  void setTranslation(const QVector3D &t);
  void setTranslation(float x, float y, float z);
  const QVector3D &translation() const;
  const QMatrix4x4 &toMatrix();

private:
  QVector3D translationVec;
  QMatrix4x4 modelWorldMatrix;
};

inline void Ball::translate(float dx, float dy, float dz) {
  translate(QVector3D(dx, dy, dz));
}

inline void Ball::setTranslation(float x, float y, float z) {
  setTranslation(QVector3D(x, y, z));
}

inline const QVector3D &Ball::translation() const { return translationVec; }

#endif // BALL_H
