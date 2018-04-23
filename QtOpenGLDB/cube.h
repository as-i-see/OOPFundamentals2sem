#ifndef CUBE_H
#define CUBE_H

#include "transform3d.h"
#include "vertex.h"
#include <QObject>
#include <QVector3D>
#include <vector>

class Cube : public QObject {
  Q_OBJECT
public:
  Cube();
  Cube(std::vector<Vertex>, QVector3D);
  Cube(const Cube &);
  ~Cube();
  Cube &operator=(const Cube &other) {
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
  bool isValid();
  void reconstructCube();
  unsigned int ID;
  void setSelected(bool);
  bool isSelected();
  Transform3D transform;
  void draw();
  void drawXYProjection();
  void drawXZProjection();
  void drawYZProjection();

private:
  std::vector<Vertex> dots;
  QVector3D color;
  bool selected;
};

#endif // CUBE_H
