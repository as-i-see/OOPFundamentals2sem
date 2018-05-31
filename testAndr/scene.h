#ifndef SCENE_H
#define SCENE_H

#include "ball.h"
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
  void restart();
  void setElasticFactor(int);

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

  int position;
  int normal;
  int modelToWorld;
  int worldToCamera;
  int cameraToView;
  int color;
  int lightDir;
  int lightColor;
  int specLightColor;
  int shine;

  QMatrix4x4 projection;

  void setupSpheres();
  void createSphere(float r, std::vector<float> &vertices);
  int p = 96;
  double R = 1.0;
};

#endif // SCENE_H
