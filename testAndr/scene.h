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

class Scene : public QOpenGLWidget {
  Q_OBJECT
public:
  Scene();
  std::vector<Ball *> balls;
  void createBallObjects();
  void handleCollisions();
  std::vector<std::pair<int, int>> collisionsOccured();
  void genStartUp();
  void resolveBallsCollision(int, int);
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
  QOpenGLBuffer cageVertex, ballsVertex;
  QOpenGLVertexArrayObject cageObject, ballsObject;

  int color;
  int position;
  int modelToWorld;
  int worldToCamera;
  int cameraToView;
  QMatrix4x4 projection;
  Transform3D transform;

  void setupSpheres();
  void createSphere(float r, std::vector<float> &vertices);
  int p = 64;
};

#endif // SCENE_H
