#ifndef PRISM_H
#define PRISM_H

#include "figure.h"

class Prism : public Figure {
  Q_OBJECT
public:
  void reconstruct();
  void draw();
  void drawXYProjection();
  void drawXZProjection();
  void drawYZProjection();
  QVector3D centreOfMass();
};

#endif // PRISM_H
