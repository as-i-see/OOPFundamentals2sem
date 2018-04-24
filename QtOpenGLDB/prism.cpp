#include "prism.h"
#include <QOpenGLFunctions>

Prism::Prism() {
  this->color = QVector3D(1.0f, 1.0f, 1.0f);
  this->selected = false;
}

Prism::Prism(const Prism &other) {
  this->dots = std::vector<Vertex>(other.dots);
  this->color = QVector3D(other.color);
  this->selected = other.selected;
  this->transform = other.transform;
}

Prism::Prism(std::vector<Vertex> dots, QVector3D color)
    : dots(dots), color(color) {
  this->selected = false;
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
                                  BA, BF, BE, BD, BC, BB,
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
    QVector3D normal = QVector3D::normal(this->dots[6 * j].position(),
                                         this->dots[6 * j + 1].position(),
                                         this->dots[6 * j + 2].position());
    glNormal3f(normal.x(), normal.y(), normal.z());
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
    QVector3D normal = QVector3D::normal(this->dots[12 + 4 * j].position(),
                                         this->dots[12 + 4 * j + 1].position(),
                                         this->dots[12 + 4 * j + 2].position());
    glNormal3f(normal.x(), normal.y(), normal.z());
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

void Prism::drawXYProjection() {
  if (this->isSelected()) {
    glColor3f(153.0f / 255.0f, 51.0f / 255.0f, 255.0f / 255.0f);
  } else {
    glColor3f(this->color.x(), this->color.y(), this->color.z());
  }
  glPushMatrix();
  for (int j = 0; j < 2; j++) {
    glBegin(GL_POLYGON);
    glVertex3f((this->transform.toMatrix() * this->dots[6 * j].position()).x(),
               (this->transform.toMatrix() * this->dots[6 * j].position()).y(),
               0);
    glVertex3f(
        (this->transform.toMatrix() * this->dots[6 * j + 1].position()).x(),
        (this->transform.toMatrix() * this->dots[6 * j + 1].position()).y(), 0);
    glVertex3f(
        (this->transform.toMatrix() * this->dots[6 * j + 2].position()).x(),
        (this->transform.toMatrix() * this->dots[6 * j + 2].position()).y(), 0);
    glVertex3f(
        (this->transform.toMatrix() * this->dots[6 * j + 3].position()).x(),
        (this->transform.toMatrix() * this->dots[6 * j + 3].position()).y(), 0);
    glVertex3f(
        (this->transform.toMatrix() * this->dots[6 * j + 4].position()).x(),
        (this->transform.toMatrix() * this->dots[6 * j + 4].position()).y(), 0);
    glVertex3f(
        (this->transform.toMatrix() * this->dots[6 * j + 5].position()).x(),
        (this->transform.toMatrix() * this->dots[6 * j + 5].position()).y(), 0);
    glEnd();
  }
  for (int j = 0; j < 6; j++) {
    glBegin(GL_QUADS);
    glVertex3f(
        (this->transform.toMatrix() * this->dots[12 + 4 * j].position()).x(),
        (this->transform.toMatrix() * this->dots[12 + 4 * j].position()).y(),
        0);
    glVertex3f(
        (this->transform.toMatrix() * this->dots[12 + 4 * j + 1].position())
            .x(),
        (this->transform.toMatrix() * this->dots[12 + 4 * j + 1].position())
            .y(),
        0);
    glVertex3f(
        (this->transform.toMatrix() * this->dots[12 + 4 * j + 2].position())
            .x(),
        (this->transform.toMatrix() * this->dots[12 + 4 * j + 2].position())
            .y(),
        0);
    glVertex3f(
        (this->transform.toMatrix() * this->dots[12 + 4 * j + 3].position())
            .x(),
        (this->transform.toMatrix() * this->dots[12 + 4 * j + 3].position())
            .y(),
        0);
    glEnd();
  }
  glPopMatrix();
}

void Prism::drawXZProjection() {
  if (this->isSelected()) {
    glColor3f(153.0f / 255.0f, 51.0f / 255.0f, 255.0f / 255.0f);
  } else {
    glColor3f(this->color.x(), this->color.y(), this->color.z());
  }
  glPushMatrix();
  for (int j = 0; j < 2; j++) {
    glBegin(GL_POLYGON);
    glVertex3f((this->transform.toMatrix() * this->dots[6 * j].position()).x(),
               0,
               (this->transform.toMatrix() * this->dots[6 * j].position()).z());
    glVertex3f(
        (this->transform.toMatrix() * this->dots[6 * j + 1].position()).x(), 0,
        (this->transform.toMatrix() * this->dots[6 * j + 1].position()).z());
    glVertex3f(
        (this->transform.toMatrix() * this->dots[6 * j + 2].position()).x(), 0,
        (this->transform.toMatrix() * this->dots[6 * j + 2].position()).z());
    glVertex3f(
        (this->transform.toMatrix() * this->dots[6 * j + 3].position()).x(), 0,
        (this->transform.toMatrix() * this->dots[6 * j + 3].position()).z());
    glVertex3f(
        (this->transform.toMatrix() * this->dots[6 * j + 4].position()).x(), 0,
        (this->transform.toMatrix() * this->dots[6 * j + 4].position()).z());
    glVertex3f(
        (this->transform.toMatrix() * this->dots[6 * j + 5].position()).x(), 0,
        (this->transform.toMatrix() * this->dots[6 * j + 5].position()).z());
    glEnd();
  }
  for (int j = 0; j < 6; j++) {
    glBegin(GL_QUADS);
    glVertex3f(
        (this->transform.toMatrix() * this->dots[12 + 4 * j].position()).x(), 0,
        (this->transform.toMatrix() * this->dots[12 + 4 * j].position()).z());
    glVertex3f(
        (this->transform.toMatrix() * this->dots[12 + 4 * j + 1].position())
            .x(),
        0,
        (this->transform.toMatrix() * this->dots[12 + 4 * j + 1].position())
            .z());
    glVertex3f(
        (this->transform.toMatrix() * this->dots[12 + 4 * j + 2].position())
            .x(),
        0,
        (this->transform.toMatrix() * this->dots[12 + 4 * j + 2].position())
            .z());
    glVertex3f(
        (this->transform.toMatrix() * this->dots[12 + 4 * j + 3].position())
            .x(),
        0,
        (this->transform.toMatrix() * this->dots[12 + 4 * j + 3].position())
            .z());
    glEnd();
  }
  glPopMatrix();
}

void Prism::drawYZProjection() {
  if (this->isSelected()) {
    glColor3f(153.0f / 255.0f, 51.0f / 255.0f, 255.0f / 255.0f);
  } else {
    glColor3f(this->color.x(), this->color.y(), this->color.z());
  }
  glPushMatrix();
  for (int j = 0; j < 2; j++) {
    glBegin(GL_POLYGON);
    glVertex3f(0,
               (this->transform.toMatrix() * this->dots[6 * j].position()).y(),
               (this->transform.toMatrix() * this->dots[6 * j].position()).z());
    glVertex3f(
        0, (this->transform.toMatrix() * this->dots[6 * j + 1].position()).y(),
        (this->transform.toMatrix() * this->dots[6 * j + 1].position()).z());
    glVertex3f(
        0, (this->transform.toMatrix() * this->dots[6 * j + 2].position()).y(),
        (this->transform.toMatrix() * this->dots[6 * j + 2].position()).z());
    glVertex3f(
        0, (this->transform.toMatrix() * this->dots[6 * j + 3].position()).y(),
        (this->transform.toMatrix() * this->dots[6 * j + 3].position()).z());
    glVertex3f(
        0, (this->transform.toMatrix() * this->dots[6 * j + 4].position()).y(),
        (this->transform.toMatrix() * this->dots[6 * j + 4].position()).z());
    glVertex3f(
        0, (this->transform.toMatrix() * this->dots[6 * j + 5].position()).y(),
        (this->transform.toMatrix() * this->dots[6 * j + 5].position()).z());
    glEnd();
  }
  for (int j = 0; j < 6; j++) {
    glBegin(GL_QUADS);
    glVertex3f(
        0, (this->transform.toMatrix() * this->dots[12 + 4 * j].position()).y(),
        (this->transform.toMatrix() * this->dots[12 + 4 * j].position()).z());
    glVertex3f(
        0,
        (this->transform.toMatrix() * this->dots[12 + 4 * j + 1].position())
            .y(),
        (this->transform.toMatrix() * this->dots[12 + 4 * j + 1].position())
            .z());
    glVertex3f(
        0,
        (this->transform.toMatrix() * this->dots[12 + 4 * j + 2].position())
            .y(),
        (this->transform.toMatrix() * this->dots[12 + 4 * j + 2].position())
            .z());
    glVertex3f(
        0,
        (this->transform.toMatrix() * this->dots[12 + 4 * j + 3].position())
            .y(),
        (this->transform.toMatrix() * this->dots[12 + 4 * j + 3].position())
            .z());
    glEnd();
  }
  glPopMatrix();
}

QVector3D Prism::centreOfMass() {
  QVector3D bottomCenter;
  for (int i = 0; i < 6; i++) {
    bottomCenter += this->dots[i].position();
  }
  bottomCenter /= 6.0f;
  QVector3D topCenter;
  for (int i = 0; i < 6; i++) {
    topCenter += this->dots[6 + i].position();
  }
  topCenter /= 6.0f;
  QVector3D center;
  center += bottomCenter;
  center += topCenter;
  center /= 2.0f;
  return center;
}
