#include "cage.h"

Cage::Cage(int l) {
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
  FTL = QVector3D(-l, l, -l);
  FBL = QVector3D(-l, -l, -l);
  FBR = QVector3D(l, -l, -l);
  FTR = QVector3D(l, l, -l);
  BTL = QVector3D(-l, l, l);
  BBL = QVector3D(-l, -l, l);
  BBR = QVector3D(l, -l, l);
  BTR = QVector3D(l, l, l);
}
