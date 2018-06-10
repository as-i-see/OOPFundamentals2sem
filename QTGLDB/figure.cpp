#include "figure.h"

Figure::Figure() {
  this->color = QVector3D(1.0f, 1.0f, 1.0f);
  this->selected = false;
}

Figure::Figure(const Figure &another) {
  this->dots = std::vector<Vertex>(another.dots);
  this->color = QVector3D(another.color);
  this->selected = another.selected;
  this->transform = another.transform;
}

Figure::Figure(std::vector<Vertex> dots, QVector3D color)
    : dots(dots), color(color) {
  this->selected = false;
}

Figure::~Figure() { this->dots.clear(); }

std::vector<Vertex> &Figure::getDots() { return this->dots; }

QVector3D Figure::getColor() { return this->color; }

void Figure::setColor(const QVector3D &color) { this->color = color; }

void Figure::setSelected(bool selected) { this->selected = selected; }

bool Figure::isSelected() { return this->selected; }
