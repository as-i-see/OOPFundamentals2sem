#ifndef CUBE_H
#define CUBE_H

#include <QObject>
#include <QVector3D>
#include <vector>
#include "vertex.h"

class Cube : public QObject {
  Q_OBJECT
 public:
  Cube();
  Cube(std::vector<Vertex>, QVector3D);
  Cube(const Cube&);
  ~Cube();
  Cube& operator=(const Cube& other) {
    if (&other == this) return *this;
    this->dots = other.dots;
    this->color = other.color;
    return *this;
  }
  std::vector<Vertex>& getDots();
  QVector3D getColor();
  void setColor(const QVector3D&);
  bool isValid();
  void reconstructCube();
  unsigned int ID;

 private:
  std::vector<Vertex> dots;
  QVector3D color;
};

#endif  // CUBE_H
