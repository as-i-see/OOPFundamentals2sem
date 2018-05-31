#ifndef TRANSFORM3D_H
#define TRANSFORM3D_H

#include <QMatrix4x4>
#include <QQuaternion>
#include <QVector3D>

class Transform3D {
public:
  // Constructors
  Transform3D();

  // Transform By (Add/Scale)
  void translate(const QVector3D &dt);
  void translate(float dx, float dy, float dz);

  // Transform To (Setters)
  void setTranslation(const QVector3D &t);
  void setTranslation(float x, float y, float z);

  // Accessors
  const QVector3D &translation() const;

  const QMatrix4x4 &toMatrix();

private:
  bool m_dirty;
  QVector3D m_translation;
  QMatrix4x4 m_world;
};

Q_DECLARE_TYPEINFO(Transform3D, Q_MOVABLE_TYPE);

inline Transform3D::Transform3D() : m_dirty(false) {}

// Transform By (Add/Scale)
inline void Transform3D::translate(float dx, float dy, float dz) {
  translate(QVector3D(dx, dy, dz));
}

// Transform To (Setters)
inline void Transform3D::setTranslation(float x, float y, float z) {
  setTranslation(QVector3D(x, y, z));
}

// Accessors
inline const QVector3D &Transform3D::translation() const {
  return m_translation;
}

#endif // TRANSFORM3D_H
