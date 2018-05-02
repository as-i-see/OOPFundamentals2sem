#ifndef FIGURE_H
#define FIGURE_H

#include "transform3d.h"
#include "vertex.h"
#include <QObject>
#include <QVector3D>
#include <vector>

class Figure : public QObject {
  Q_OBJECT
public:
  Figure();
  Figure(std::vector<Vertex>, QVector3D);
  Figure(const Figure &);
  ~Figure();
  Figure &operator=(const Figure &other) {
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
  void setSelected(bool);
  bool isSelected();

  virtual void reconstruct() = 0;
  virtual void draw() = 0;
  virtual void drawXYProjection() = 0;
  virtual void drawXZProjection() = 0;
  virtual void drawYZProjection() = 0;
  virtual QVector3D centreOfMass() = 0;

  unsigned int ID;
  Transform3D transform;

protected:
  std::vector<Vertex> dots;
  QVector3D color;
  bool selected;
};

#endif // FIGURE_H
