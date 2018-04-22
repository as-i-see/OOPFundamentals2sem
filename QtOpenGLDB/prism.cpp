#include "prism.h"
#include <QOpenGLFunctions>

Prism::Prism() {
  this->color = QVector3D(1.0f, 1.0f, 1.0f);
  this->selected = false;
  this->transform.translate(0.0f, 0.0f, -5.0f);
}

Prism::Prism(const Prism &other) {
  this->dots = std::vector<Vertex>(other.dots);
  this->color = QVector3D(other.color);
  this->selected = other.selected;
  this->transform.translate(0.0f, 0.0f, -5.0f);
}

Prism::Prism(std::vector<Vertex> dots, QVector3D color)
    : dots(dots), color(color) {
  this->selected = false;
  this->transform.translate(0.0f, 0.0f, -5.0f);
}

Prism::~Prism() { this->dots.clear(); }

void Prism::reconstructPrism() {
  Vertex BA(this->dots[0].position());
  Vertex BB(this->dots[1].position());
  Vertex BC(this->dots[2].position());
  Vertex BD(this->dots[3].position());
  Vertex BE(this->dots[4].position());
  Vertex BF(this->dots[5].position());
  Vertex TA(this->dots[6].position());
  QVector3D upVector = TA.position() - BA.position();
  Vertex TB(BB.position() + upVector);
  Vertex TC(BC.position() + upVector);
  Vertex TD(BD.position() + upVector);
  Vertex TE(BE.position() + upVector);
  Vertex TF(BF.position() + upVector);
  std::vector<Vertex> vertices = {// Bottom
                                  BA, BB, BC, BD, BE, BF,
                                  // Top
                                  TA, TB, TC, TD, TE, TF,
                                  // Face 1
                                  BA, BB, TB, TA,
                                  // Face 2
                                  BB, BC, TC, TB,
                                  // Face 3
                                  BC, BD, TD, TC,
                                  // Face 4
                                  BD, BE, TE, TD,
                                  // Face 5
                                  BE, BF, TF, TE,
                                  // Face 6
                                  BF, BA, TA, TF};
  this->dots = std::move(vertices);
}

std::vector<Vertex> &Prism::getDots() { return this->dots; }

QVector3D Prism::getColor() { return this->color; }

void Prism::setColor(const QVector3D &color) { this->color = color; }

void Prism::setSelected(bool selected) { this->selected = selected; }

bool Prism::isSelected() { return this->selected; }

void Prism::draw() {
  if (this->isSelected()) {
    glColor3f(153.0f / 255.0f, 51.0f / 255.0f, 255.0f / 255.0f);
  } else {
    glColor3f(this->color.x(), this->color.y(), this->color.z());
  }
  glPushMatrix();
  glLoadMatrixf(this->transform.toMatrix().data());
  for (int j = 0; j < 2; j++) {
    glBegin(GL_POLYGON);
    glVertex3f(this->dots[6 * j].position().x(),
               this->dots[6 * j].position().y(),
               this->dots[6 * j].position().z());
    glVertex3f(this->dots[6 * j + 1].position().x(),
               this->dots[6 * j + 1].position().y(),
               this->dots[6 * j + 1].position().z());
    glVertex3f(this->dots[6 * j + 2].position().x(),
               this->dots[6 * j + 2].position().y(),
               this->dots[6 * j + 2].position().z());
    glVertex3f(this->dots[6 * j + 3].position().x(),
               this->dots[6 * j + 3].position().y(),
               this->dots[6 * j + 3].position().z());
    glVertex3f(this->dots[6 * j + 4].position().x(),
               this->dots[6 * j + 4].position().y(),
               this->dots[6 * j + 4].position().z());
    glVertex3f(this->dots[6 * j + 5].position().x(),
               this->dots[6 * j + 5].position().y(),
               this->dots[6 * j + 5].position().z());
    glEnd();
  }
  for (int j = 0; j < 6; j++) {
    glBegin(GL_QUADS);
    glVertex3f(this->dots[12 + 4 * j].position().x(),
               this->dots[12 + 4 * j].position().y(),
               this->dots[12 + 4 * j].position().z());
    glVertex3f(this->dots[12 + 4 * j + 1].position().x(),
               this->dots[12 + 4 * j + 1].position().y(),
               this->dots[12 + 4 * j + 1].position().z());
    glVertex3f(this->dots[12 + 4 * j + 2].position().x(),
               this->dots[12 + 4 * j + 2].position().y(),
               this->dots[12 + 4 * j + 2].position().z());
    glVertex3f(this->dots[12 + 4 * j + 3].position().x(),
               this->dots[12 + 4 * j + 3].position().y(),
               this->dots[12 + 4 * j + 3].position().z());
    glEnd();
  }
  glPopMatrix();
}
