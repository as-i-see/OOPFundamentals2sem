#include "Transform3D.h"
#include <QDebug>

// Transform By (Add/Scale)
void Transform3D::translate(const QVector3D &dt) {
  m_dirty = true;
  m_translation += dt;
}

// Transform To (Setters)
void Transform3D::setTranslation(const QVector3D &t) {
  m_dirty = true;
  m_translation = t;
}

// Accessors
const QMatrix4x4 &Transform3D::toMatrix() {
  if (m_dirty) {
    m_dirty = false;
    m_world.setToIdentity();
    m_world.translate(m_translation);
  }
  return m_world;
}
