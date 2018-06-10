#ifndef CYLINDER_H
#define CYLINDER_H

#include "figure.h"

class Cylinder : public Figure {
  Q_OBJECT
public:
  void reconstruct();
  void draw();
  void drawXYProjection();
  void drawXZProjection();
  void drawYZProjection();
  QVector3D centreOfMass();
  void setRadius(double);
  const double &getRadius();
  void setHeight(double);
  const double &getHeight();

private:
  double radius;
  double height;
};

#endif // CUBE_H
