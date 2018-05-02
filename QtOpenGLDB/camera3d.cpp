#include "camera3d.h"
#include <QDebug>

const QVector3D Camera3D::LocalForward(0.0f, 0.0f, -1.0f);
const QVector3D Camera3D::LocalUp(0.0f, 1.0f, 0.0f);
const QVector3D Camera3D::LocalRight(1.0f, 0.0f, 0.0f);

// Transform By (Add/Scale)
void Camera3D::translate(const QVector3D &dt) {
  m_dirty = true;
  m_translation += dt;
}

void Camera3D::rotate(const QQuaternion &dr) {
  m_dirty = true;
  m_rotation = dr * m_rotation;
}

// Transform To (Setters)
void Camera3D::setTranslation(const QVector3D &t) {
  m_dirty = true;
  m_translation = t;
}

void Camera3D::setRotation(const QQuaternion &r) {
  m_dirty = true;
  m_rotation = r;
}

// Accessors
const QMatrix4x4 &Camera3D::toMatrix() {
  if (m_dirty) {
    m_dirty = false;
    m_world.setToIdentity();
    m_world.rotate(m_rotation.conjugate());
    m_world.translate(-m_translation);
  }
  return m_world;
}

// Queries
QVector3D Camera3D::forward() const {
  return m_rotation.rotatedVector(LocalForward);
}

QVector3D Camera3D::right() const {
  return m_rotation.rotatedVector(LocalRight);
}

QVector3D Camera3D::up() const { return m_rotation.rotatedVector(LocalUp); }
