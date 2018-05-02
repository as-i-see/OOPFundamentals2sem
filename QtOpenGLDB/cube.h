#ifndef CUBE_H
#define CUBE_H

#include "figure.h"

class Cube : public Figure {
  Q_OBJECT
public:
  bool isValid();
  void reconstruct();
  void draw();
  void drawXYProjection();
  void drawXZProjection();
  void drawYZProjection();
  QVector3D centreOfMass();
};

#endif // CUBE_H
