#include "cube.h"
#include <QDebug>
#include <QOpenGLFunctions>
#include <cmath>

Cube::Cube() {
  this->color = QVector3D(1.0f, 1.0f, 1.0f);
  this->selected = false;
}

Cube::Cube(const Cube &anotherCube) {
  this->dots = std::vector<Vertex>(anotherCube.dots);
  this->color = QVector3D(anotherCube.color);
  this->selected = anotherCube.selected;
  this->transform = anotherCube.transform;
}

Cube::Cube(std::vector<Vertex> dots, QVector3D color)
    : dots(dots), color(color) {
  this->selected = false;
}

Cube::~Cube() { this->dots.clear(); }

std::vector<Vertex> &Cube::getDots() { return this->dots; }

QVector3D Cube::getColor() { return this->color; }

void Cube::setColor(const QVector3D &color) { this->color = color; }

bool Cube::isValid() {
  if (this->dots.size() != 4)
    return false;
  float sideLen =
      this->dots[0].position().distanceToPoint(this->dots[1].position());
  float diagonalLen = pow(2.0, 0.5) * sideLen;
  bool isCube = true;
  isCube = (this->dots[0].position().distanceToPoint(
                this->dots[2].position()) == sideLen);
  isCube = (this->dots[0].position().distanceToPoint(
                this->dots[3].position()) == sideLen);
  isCube = (this->dots[1].position().distanceToPoint(
                this->dots[2].position()) == diagonalLen);
  isCube = (this->dots[1].position().distanceToPoint(
                this->dots[3].position()) == diagonalLen);
  isCube = (this->dots[2].position().distanceToPoint(
                this->dots[3].position()) == diagonalLen);
  return isCube;
}

void Cube::reconstructCube() {
  Vertex VERTEX_FBL(this->dots[0].position());
  Vertex VERTEX_FBR(this->dots[1].position());
  Vertex VERTEX_FTL(this->dots[3].position());
  Vertex VERTEX_BBL(this->dots[2].position());
  QVector3D upVector = VERTEX_FTL.position() - VERTEX_FBL.position();
  QVector3D frontwardVector = VERTEX_BBL.position() - VERTEX_FBL.position();
  Vertex VERTEX_FTR(VERTEX_FBR.position() + upVector);
  Vertex VERTEX_BTL(VERTEX_FTL.position() + frontwardVector);
  Vertex VERTEX_BTR(VERTEX_FTR.position() + frontwardVector);
  Vertex VERTEX_BBR(VERTEX_FBR.position() + frontwardVector);
  std::vector<Vertex> vertices = {
      // Face 1 (Front)
      VERTEX_FTR, VERTEX_FTL, VERTEX_FBL, VERTEX_FBR,
      // Face 2 (Back)
      VERTEX_BBR, VERTEX_BBL, VERTEX_BTL, VERTEX_BTR,
      // Face 3 (Top)
      VERTEX_FTR, VERTEX_FTL, VERTEX_BTL, VERTEX_BTR,
      // Face 4 (Bottom)
      VERTEX_FBR, VERTEX_FBL, VERTEX_BBL, VERTEX_BBR,
      // Face 5 (Left)
      VERTEX_FBL, VERTEX_FTL, VERTEX_BTL, VERTEX_BBL,
      // Face 6 (Right)
      VERTEX_FTR, VERTEX_FBR, VERTEX_BBR, VERTEX_BTR};
  this->dots = std::move(vertices);
}

void Cube::setSelected(bool selected) { this->selected = selected; }

bool Cube::isSelected() { return this->selected; }

void Cube::draw() {
  if (this->isSelected()) {
    glColor3f(153.0f / 255.0f, 51.0f / 255.0f, 255.0f / 255.0f);
  } else {
    glColor3f(this->color.x(), this->color.y(), this->color.z());
  }
  glPushMatrix();
  glLoadMatrixf(this->transform.toMatrix().data());
  for (int j = 0; j < 6; j++) {
    glBegin(GL_QUADS);
    glVertex3f(this->dots[4 * j].position().x(),
               this->dots[4 * j].position().y(),
               this->dots[4 * j].position().z());
    glVertex3f(this->dots[4 * j + 1].position().x(),
               this->dots[4 * j + 1].position().y(),
               this->dots[4 * j + 1].position().z());
    glVertex3f(this->dots[4 * j + 2].position().x(),
               this->dots[4 * j + 2].position().y(),
               this->dots[4 * j + 2].position().z());
    glVertex3f(this->dots[4 * j + 3].position().x(),
               this->dots[4 * j + 3].position().y(),
               this->dots[4 * j + 3].position().z());
    glEnd();
  }
  glPopMatrix();
}
