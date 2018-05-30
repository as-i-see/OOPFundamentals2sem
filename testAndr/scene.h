#ifndef SCENE_H
#define SCENE_H

#include "ball.h"
#include "transform3d.h"
#include <QObject>
#include <QOpenGLBuffer>
#include <QOpenGLContext>
#include <QOpenGLExtraFunctions>
#include <QOpenGLFramebufferObject>
#include <QOpenGLFunctions>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLWidget>
#include <QtOpenGL/QtOpenGL>
#include <QtOpenGL>
#include <qopengl.h>

class Scene : public QOpenGLWidget {
  Q_OBJECT
public:
  Scene();
public slots:
  void start();

protected:
  void initializeGL();
  void resizeGL(int, int);
  void paintGL();
protected slots:
  void update();

private:
  QOpenGLShaderProgram *program;
  std::vector<Ball *> balls;
  QOpenGLBuffer cageVertex, ballsVertex;
  QOpenGLVertexArrayObject cageObject, ballsObject;

  int color;
  int position;
  int modelToWorld;
  int worldToCamera;
  int cameraToView;
  QMatrix4x4 projection;
  Transform3D transform;
  void genStartUp();
  std::vector<std::pair<int, int>> collisionsOccured();
  void handleCollisions();
  void resolveBallsCollision(int, int);

  void renderSphere(float cx, float cy, float cz, float r, int p,
                    QVector3D ballColor);
};

#endif // SCENE_H
