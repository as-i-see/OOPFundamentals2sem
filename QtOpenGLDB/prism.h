#ifndef PRISM_H
#define PRISM_H

#include "transform3d.h"
#include "vertex.h"
#include <QObject>
#include <QVector3D>
#include <vector>

class Prism : public QObject {
  Q_OBJECT
public:
  Prism();
  Prism(const Prism &);
  Prism(std::vector<Vertex>, QVector3D);
  ~Prism();
  Prism &operator=(const Prism &other) {
    if (&other == this)
      return *this;
    this->dots = other.dots;
    this->color = other.color;
    this->transform = other.transform;
    return *this;
  }
  std::vector<Vertex> &getDots();
  QVector3D getColor();
  void setColor(const QVector3D &);
  void reconstructPrism();
  unsigned int ID;
  void setSelected(bool);
  bool isSelected();
  Transform3D transform;
  void draw();
  void drawXYProjection();
  void drawXZProjection();
  void drawYZProjection();
  QVector3D centreOfMass();

private:
  std::vector<Vertex> dots;
  QVector3D color;
  bool selected;
};

#endif // PRISM_H
