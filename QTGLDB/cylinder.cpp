#include "cylinder.h"
#include <QDebug>
#include <QOpenGLFunctions>
#include <QQuaternion>
#include <cmath>

const double &Cylinder::getRadius() { return radius; }
Cylinder::setRadius(double radius) { this->radius = radius; }
const double &Cylinder::getHeight() { return height; }
Cylinder::setHeight(double height) { this->height = height; }

void Cylinder::reconstruct() {
  Vertex BC(this->dots[0].position());
  QQuaternion rotQ = QQuaternion::fromAxisAndAngle(0.0f, 0.0f, 1.0f, 20.0f);
  std::vector<Vertex> vertices;
  QVector3D radiusVector(1.0f, 0.0f, 0.0f);
  vertices.push_back(radiusVector);
  for (int i = 1; i < 18; i++) {
    radiusVector = rotQ.rotatedVector(vertices[i - 1]);
    vertices.push_back(radiusVector);
  }

  QVector3D upVector = TC - BC;
  QVector3D upVectorXYProj = QVector3D(upVector.x(), upVector.y(), 0);
  QVector3D croppedToRadius = upVectorXYProj * (radius / upVector.length());

  this->dots = std::move(vertices);
}

void Cylinder::draw() {
  if (this->isSelected()) {
    glColor3f(153.0f / 255.0f, 51.0f / 255.0f, 255.0f / 255.0f);
  } else {
    glColor3f(this->color.x(), this->color.y(), this->color.z());
  }
  glPushMatrix();
  glLoadMatrixf(this->transform.toMatrix().data());

  for (int j = 0; j < 6; j++) {
    glBegin(GL_QUADS);
    QVector3D normal = QVector3D::normal(this->dots[4 * j].position(),
                                         this->dots[4 * j + 1].position(),
                                         this->dots[4 * j + 2].position());
    glNormal3f(normal.x(), normal.y(), normal.z());
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

void Cylinder::drawXYProjection() {
  if (this->isSelected()) {
    glColor3f(153.0f / 255.0f, 51.0f / 255.0f, 255.0f / 255.0f);
  } else {
    glColor3f(this->color.x(), this->color.y(), this->color.z());
  }
  for (int j = 0; j < 6; j++) {
    glBegin(GL_QUADS);
    glVertex3f((this->transform.toMatrix() * this->dots[4 * j].position()).x(),
               (this->transform.toMatrix() * this->dots[4 * j].position()).y(),
               0);
    glVertex3f(
        (this->transform.toMatrix() * this->dots[4 * j + 1].position()).x(),
        (this->transform.toMatrix() * this->dots[4 * j + 1].position()).y(), 0);
    glVertex3f(
        (this->transform.toMatrix() * this->dots[4 * j + 2].position()).x(),
        (this->transform.toMatrix() * this->dots[4 * j + 2].position()).y(), 0);
    glVertex3f(
        (this->transform.toMatrix() * this->dots[4 * j + 3].position()).x(),
        (this->transform.toMatrix() * this->dots[4 * j + 3].position()).y(), 0);
    glEnd();
  }
}

void Cylinder::drawXZProjection() {
  if (this->isSelected()) {
    glColor3f(153.0f / 255.0f, 51.0f / 255.0f, 255.0f / 255.0f);
  } else {
    glColor3f(this->color.x(), this->color.y(), this->color.z());
  }
  for (int j = 0; j < 6; j++) {
    glBegin(GL_QUADS);
    glVertex3f((this->transform.toMatrix() * this->dots[4 * j].position()).x(),
               0,
               (this->transform.toMatrix() * this->dots[4 * j].position()).z());
    glVertex3f(
        (this->transform.toMatrix() * this->dots[4 * j + 1].position()).x(), 0,
        (this->transform.toMatrix() * this->dots[4 * j + 1].position()).z());
    glVertex3f(
        (this->transform.toMatrix() * this->dots[4 * j + 2].position()).x(), 0,
        (this->transform.toMatrix() * this->dots[4 * j + 2].position()).z());
    glVertex3f(
        (this->transform.toMatrix() * this->dots[4 * j + 3].position()).x(), 0,
        (this->transform.toMatrix() * this->dots[4 * j + 3].position()).z());
    glEnd();
  }
}

void Cylinder::drawYZProjection() {
  if (this->isSelected()) {
    glColor3f(153.0f / 255.0f, 51.0f / 255.0f, 255.0f / 255.0f);
  } else {
    glColor3f(this->color.x(), this->color.y(), this->color.z());
  }
  for (int j = 0; j < 6; j++) {
    glBegin(GL_QUADS);
    glVertex3f(0,
               (this->transform.toMatrix() * this->dots[4 * j].position()).y(),
               (this->transform.toMatrix() * this->dots[4 * j].position()).z());
    glVertex3f(
        0, (this->transform.toMatrix() * this->dots[4 * j + 1].position()).y(),
        (this->transform.toMatrix() * this->dots[4 * j + 1].position()).z());
    glVertex3f(
        0, (this->transform.toMatrix() * this->dots[4 * j + 2].position()).y(),
        (this->transform.toMatrix() * this->dots[4 * j + 2].position()).z());
    glVertex3f(
        0, (this->transform.toMatrix() * this->dots[4 * j + 3].position()).y(),
        (this->transform.toMatrix() * this->dots[4 * j + 3].position()).z());
    glEnd();
  }
}

QVector3D Cylinder::centreOfMass() {
  QVector3D com;
  for (int i = 0; i < 8; i++) {
    com += this->dots[i].position();
  }
  com /= 8.0f;
  return com;
}
