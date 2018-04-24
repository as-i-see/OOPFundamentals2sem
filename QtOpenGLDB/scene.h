#ifndef SCENE_H
#define SCENE_H
#include "camera3d.h"
#include "cube.h"
#include "prism.h"
#include "transform3d.h"
#include "vertex.h"
#include <QColorDialog>
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
  QColorDialog *colorDialog;
public slots:
  void rotateX();
  void rotateY();
  void rotateZ();
  void showXYProjection();
  void showYZProjection();
  void showXZProjection();
  void moveXPos();
  void moveXNeg();
  void moveYPos();
  void moveYNeg();
  void moveZPos();
  void moveZNeg();
  void scale();
  void changeColor(QColor);
  void loadScene(std::pair<std::vector<Cube>, std::vector<Prism>>);
  void sceneConfigRequest(std::pair<std::vector<Cube>, std::vector<Prism>> &);
  void setPreferences(std::vector<float>);

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

  QMatrix4x4 m_projection;
  Transform3D m_transform;
  Camera3D m_camera;

  std::vector<QVector3D> coordsColors = {QVector3D(1.0f, 0.0f, 0.0f),
                                         QVector3D(0.0f, 1.0f, 0.0f),
                                         QVector3D(0.0f, 0.0f, 1.0f)};
  QVector3D whiteColor = QVector3D(1.0f, 1.0f, 1.0f);

  QVector3D selectionColor =
      QVector3D(153.0f / 255.0f, 51.0f / 255.0f, 255.0f / 255.0f);

  std::vector<Vertex> coordAxes;
  std::vector<Vertex> getCoordAxes();
  void drawCoordAxes();
  std::vector<int> selectedCubes;
  std::vector<int> selectedPrisms;

  int retrieveObjectID(int x, int y);

  bool showXY = false;
  bool showYZ = false;
  bool showXZ = false;

  float rotationAngle = 15.0f;
  float translationUnit = 1.0f;
  float scalingFactor = 1.5f;
};

#endif // SCENE_H
