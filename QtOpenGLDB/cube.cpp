#include "cube.h"
#include <cmath>

Cube::Cube() { this->color = QVector3D(1.0f, 1.0f, 1.0f); }

Cube::Cube(const Cube& anotherCube) {
  this->dots = std::vector<Vertex>(anotherCube.dots);
  this->color = QVector3D(anotherCube.color);
}

Cube::Cube(std::vector<Vertex> dots, QVector3D color)
    : dots(dots), color(color) {}

Cube::~Cube() { this->dots.clear(); }

std::vector<Vertex>& Cube::getDots() { return this->dots; }

QVector3D Cube::getColor() { return this->color; }

void Cube::setColor(const QVector3D& color) { this->color = color; }

bool Cube::isValid() {
  if (this->dots.size() != 4) return false;
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
  this->color = QVector3D(1.0f, 1.0f, 1.0f);
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
      VERTEX_FTR, VERTEX_FTL, VERTEX_FBL, VERTEX_FBL, VERTEX_FBR, VERTEX_FTR,
      // Face 2 (Back)
      VERTEX_BBR, VERTEX_BTL, VERTEX_BTR, VERTEX_BTL, VERTEX_BBR, VERTEX_BBL,
      // Face 3 (Top)
      VERTEX_FTR, VERTEX_BTR, VERTEX_BTL, VERTEX_BTL, VERTEX_FTL, VERTEX_FTR,
      // Face 4 (Bottom)
      VERTEX_FBR, VERTEX_FBL, VERTEX_BBL, VERTEX_BBL, VERTEX_BBR, VERTEX_FBR,
      // Face 5 (Left)
      VERTEX_FBL, VERTEX_FTL, VERTEX_BTL, VERTEX_FBL, VERTEX_BTL, VERTEX_BBL,
      // Face 6 (Right)
      VERTEX_FTR, VERTEX_FBR, VERTEX_BBR, VERTEX_BBR, VERTEX_BTR, VERTEX_FTR};
  this->dots = std::move(vertices);
}
