#include "cage.h"

#define l 50.0f

Cage::Cage() {
  dots.push_back(QVector3D(l, l, l));
  dots.push_back(QVector3D(l, l, -l));
  dots.push_back(QVector3D(-l, l, l));
  dots.push_back(QVector3D(-l, l, -l));
  dots.push_back(QVector3D(l, -l, l));
  dots.push_back(QVector3D(l, -l, -l));
  dots.push_back(QVector3D(-l, -l, l));
  dots.push_back(QVector3D(-l, -l, -l));
  dots.push_back(QVector3D(l, l, l));
  dots.push_back(QVector3D(-l, l, l));
  dots.push_back(QVector3D(l, l, -l));
  dots.push_back(QVector3D(-l, l, -l));
  dots.push_back(QVector3D(l, -l, l));
  dots.push_back(QVector3D(-l, -l, l));
  dots.push_back(QVector3D(l, -l, -l));
  dots.push_back(QVector3D(-l, -l, -l));
  dots.push_back(QVector3D(l, l, l));
  dots.push_back(QVector3D(l, -l, l));
  dots.push_back(QVector3D(-l, l, l));
  dots.push_back(QVector3D(-l, -l, l));
  dots.push_back(QVector3D(l, l, -l));
  dots.push_back(QVector3D(l, -l, -l));
  dots.push_back(QVector3D(-l, l, -l));
  dots.push_back(QVector3D(-l, -l, -l));
}
