#ifndef SCENE_H
#define SCENE_H
#include "camera3d.h"
#include "cube.h"
#include "prism.h"
#include "transform3d.h"
#include "vertex.h"
#include <QMatrix4x4>
#include <QMouseEvent>
#include <QOpenGLBuffer>
#include <QOpenGLFunctions>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLWidget>
#include <vector>

class QOpenGLShaderProgram;

class Scene : public QOpenGLWidget //, protected QOpenGLFunctions
{
  Q_OBJECT
public:
  Scene(QWidget *parent);
  std::vector<Cube> cubes;
  std::vector<Prism> prisms;
  bool multipleFaceMode, multipleFigureMode;
  float rotationAngle = 15.0f;
public slots:
  void reloadScene();
  void rotateX();
  void rotateY();
  void rotateZ();
  void showXYProjection();
  void showYZProjection();
  void showZXProjection();
  void moveLeft();
  void moveRight();
  void moveDown();
  void moveUp();
  void moveBackward();
  void moveFrontward();

protected:
  void initializeGL();
  void resizeGL(int, int);
  void paintGL();
  void keyPressEvent(QKeyEvent *event);
  void keyReleaseEvent(QKeyEvent *event);
  void mousePressEvent(QMouseEvent *event);
  void mouseReleaseEvent(QMouseEvent *event);
protected slots:
  void update();

private:
  QPoint lastPos;
  int w, h;
  QOpenGLShaderProgram *m_program;
  QOpenGLVertexArrayObject cubeVAO, coordsVAO;
  QOpenGLBuffer cubesVBO, coordsVBO;

  // Shader Information
  int u_modelToWorld;
  int u_worldToCamera;
  int u_cameraToView;
  int u_figureColor;
  QMatrix4x4 m_projection;
  Transform3D m_transform;
  Camera3D m_camera;

  QVector3D redColor = QVector3D(1.0f, 0.0f, 0.0f);
  QVector3D greenColor = QVector3D(0.0f, 1.0f, 0.0f);
  QVector3D blueColor = QVector3D(0.0f, 0.0f, 1.0f);
  QVector3D whiteColor = QVector3D(1.0f, 1.0f, 1.0f);
  QVector3D selectionColor =
      QVector3D(153.0f / 255.0f, 51.0f / 255.0f, 255.0f / 255.0f);

  void reloadSetup();

  std::vector<std::vector<Vertex>> getCoords();
  std::vector<Vertex> getAxes();
  std::vector<int> selected;

  int retrieveObjectID(int x, int y);
};

#endif // SCENE_H
