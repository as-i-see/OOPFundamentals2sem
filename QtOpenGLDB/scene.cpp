#include "scene.h"
#include "GL/GLU.h"
#include "cube.h"
#include "input.h"
#include "vertex.h"
#include <QDebug>
#include <QMatrix4x4>
#include <QOpenGLShaderProgram>
#include <QPoint>
#include <QScreen>
#include <QString>
#include <QSurfaceFormat>

Scene::Scene(QWidget *parent) : QOpenGLWidget(parent) {
  QSurfaceFormat format;
  format.setDepthBufferSize(24);
  format.setSwapBehavior(QSurfaceFormat::DoubleBuffer);
  setFormat(format);
  m_transform.translate(0.0f, 0.0f, -5.0f);
}

void Scene::initializeGL() {
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  connect(this, SIGNAL(frameSwapped()), this, SLOT(update()));
  glEnable(GL_DEPTH_TEST);
  glClearDepth(1.0f);
  glDepthFunc(GL_LEQUAL);
  // glEnable(GL_CULL_FACE);

  glLineWidth(0.1f);

  m_program = new QOpenGLShaderProgram();
  m_program->addShaderFromSourceFile(QOpenGLShader::Vertex,
                                     ":/shaders/simple.vert");
  m_program->addShaderFromSourceFile(QOpenGLShader::Fragment,
                                     ":/shaders/simple.frag");
  m_program->link();
  m_program->bind();

  /////////////////////////////////

  cubeVAO.create();
  cubeVAO.bind();

  u_modelToWorld = m_program->uniformLocation("modelToWorld");
  u_worldToCamera = m_program->uniformLocation("worldToCamera");
  u_cameraToView = m_program->uniformLocation("cameraToView");
  u_figureColor = m_program->uniformLocation("figureColor");

  cubesVBO.create();
  cubesVBO.setUsagePattern(QOpenGLBuffer::DynamicDraw);
  cubesVBO.bind();

  m_program->enableAttributeArray(0);
  m_program->setAttributeBuffer(0, GL_FLOAT, 0, 3, 24);

  cubesVBO.release();
  cubeVAO.release();

  //////////////////////////////////

  coordsVAO.create();
  coordsVAO.bind();

  coordsVBO.create();
  coordsVBO.setUsagePattern(QOpenGLBuffer::StaticDraw);
  coordsVBO.bind();

  m_program->enableAttributeArray(0);
  m_program->setAttributeBuffer(0, GL_FLOAT, 0, 3, 24);

  auto coordsVec = getCoords();
  coordsVBO.allocate(15120);
  for (unsigned i = 0; i < 3; i++) {
    auto ptr = coordsVBO.mapRange(i * 4992, 4992,
                                  QOpenGLBuffer::RangeInvalidate |
                                      QOpenGLBuffer::RangeWrite);
    memcpy(ptr, coordsVec[i].data(), 4992);
    coordsVBO.unmap();
  }
  auto axesVec = getAxes();
  auto ptr = coordsVBO.mapRange(
      14976, 144, QOpenGLBuffer::RangeInvalidate | QOpenGLBuffer::RangeWrite);
  memcpy(ptr, axesVec.data(), 144);
  coordsVBO.unmap();

  coordsVBO.release();
  coordsVAO.release();

  m_program->release();
}

void Scene::resizeGL(int w, int h) {
  m_projection.setToIdentity();
  m_projection.perspective(45.0f, w / float(h), 1.0f, 200.0f);
  this->w = w;
  this->h = h;
}

void Scene::paintGL() {

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glEnable(GL_DEPTH_TEST);
  glClearDepth(1.0f);
  glDepthFunc(GL_LEQUAL);
  glViewport(0, 0, w, h);
  glLineWidth(0.1f);
  m_program->bind();

  coordsVAO.bind();
  m_program->setUniformValue(u_cameraToView, m_projection);
  m_program->setUniformValue(u_worldToCamera, m_camera.toMatrix());
  m_program->setUniformValue(u_modelToWorld, m_transform.toMatrix()); // yeah
  m_program->setUniformValue(u_figureColor, this->redColor);
  glDrawArrays(GL_LINES, 0, 208);
  m_program->setUniformValue(u_figureColor, this->greenColor);
  glDrawArrays(GL_LINES, 208, 208);
  m_program->setUniformValue(u_figureColor, this->blueColor);
  glDrawArrays(GL_LINES, 416, 208);
  glLineWidth(2.0f);
  m_program->setUniformValue(u_figureColor, this->whiteColor);
  glDrawArrays(GL_LINES, 624, 630);
  coordsVAO.release();

  cubeVAO.bind();
  m_program->setUniformValue(u_cameraToView, m_projection);
  for (int i = 0; i < this->cubes.size(); i++) {
    m_program->setUniformValue(u_figureColor, this->cubes[i].getColor());
    // m_program->setUniformValue(u_figureColor, this->idColors[i]);
    glDrawArrays(GL_TRIANGLES, 36 * i, 36);
  }
  cubeVAO.release();

  m_program->release();
}

static void qNormalizeAngle(int &angle) {
  while (angle < 0)
    angle += 360 * 16;
  while (angle > 360)
    angle -= 360 * 16;
}

void Scene::update() {
  // Update input
  Input::update();

  static const float transSpeed = 0.5f;
  static const float rotSpeed = 0.5f;

  // Camera Transformation
  if (Input::buttonPressed(Qt::RightButton)) {
    // Handle rotations
    m_camera.rotate(-rotSpeed * Input::mouseDelta().x(), Camera3D::LocalUp);
    m_camera.rotate(-rotSpeed * Input::mouseDelta().y(), m_camera.right());
  }
  // Handle translations
  QVector3D translation;
  if (Input::keyPressed(Qt::Key_W)) {
    translation += m_camera.forward();
  }
  if (Input::keyPressed(Qt::Key_S)) {
    translation -= m_camera.forward();
  }
  if (Input::keyPressed(Qt::Key_A)) {
    translation -= m_camera.right();
  }
  if (Input::keyPressed(Qt::Key_D)) {
    translation += m_camera.right();
  }
  if (Input::keyPressed(Qt::Key_Q)) {
    translation -= m_camera.up();
  }
  if (Input::keyPressed(Qt::Key_E)) {
    translation += m_camera.up();
  }
  m_camera.translate(transSpeed * translation);

  if (Input::buttonPressed(Qt::LeftButton)) {
    QPoint globalClick(Input::mousePosition().x(), Input::mousePosition().y());
    QPoint localClick = this->mapFromGlobal(globalClick);
    int properX = localClick.x();
    int properY = h - localClick.y();
    int selectedObjectID = retrieveObjectID(properX, properY);
    qDebug() << selectedObjectID;
    Input::registerMouseRelease(Qt::LeftButton);
  }

  // Update instance information
  // m_transform.rotate(1.0f, QVector3D(0.4f, 0.3f, 0.3f));
  // Input::reset();
  // Schedule a redraw
  QOpenGLWidget::update();
}

int Scene::retrieveObjectID(int x, int y) {

  int objectsFound = 0;
  int viewportCoords[4] = {0};
  unsigned int selectBuffer[32] = {0};
  glSelectBuffer(32, selectBuffer);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glEnable(GL_DEPTH_TEST);
  glClearDepth(1.0f);
  glDepthFunc(GL_LEQUAL);
  glViewport(0, 0, w, h);
  glGetIntegerv(GL_VIEWPORT, viewportCoords);
  glMatrixMode(GL_PROJECTION);
  glPushMatrix();
  glLoadIdentity();

  glRenderMode(GL_SELECT);

  viewportCoords[2] = w;
  viewportCoords[3] = h;

  gluPickMatrix(x, y, 2, 2, viewportCoords);
  gluPerspective(45.0, (float)w / (float)h, 1.0, 200.0);

  GLfloat projectionMatrix[16] = {0};
  glGetFloatv(GL_PROJECTION_MATRIX, projectionMatrix);
  QMatrix4x4 projection(projectionMatrix);
  m_program->bind();
  cubeVAO.bind();
  m_program->setUniformValue(u_cameraToView, projection);
  m_program->setUniformValue(u_modelToWorld, m_transform.toMatrix());
  glMatrixMode(GL_MODELVIEW);
  ////////////////////RENDER
  ///
  ///
  ///
  ///

  m_program->setUniformValue(u_worldToCamera, m_camera.toMatrix());
  glInitNames();
  glPushName(0);

  for (int i = 0; i < this->cubes.size(); i++) {
    glLoadName(this->cubes[i].ID);
    m_program->setUniformValue(u_figureColor, this->cubes[i].getColor());
    glDrawArrays(GL_TRIANGLES, 36 * i, 36);
  }
  glPopName();
  // glLoadName(0);
  glMatrixMode(GL_PROJECTION);
  glPopMatrix();
  glMatrixMode(GL_MODELVIEW);
  objectsFound = glRenderMode(GL_RENDER);

  m_projection.setToIdentity();
  m_projection.perspective(45.0f, w / float(h), 1.0f, 200.0f);
  m_program->setUniformValue(u_cameraToView, m_projection);
  cubeVAO.release();
  m_program->release();
  // glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
  int selectedObject = 0;
  if (objectsFound > 0) {
    unsigned int lowestDepth = selectBuffer[1];
    selectedObject = selectBuffer[3];
    for (int i = 1; i < objectsFound; i++) {
      if (selectBuffer[(i * 4) + 1] < lowestDepth) {
        lowestDepth = selectBuffer[(i * 4) + 1];
        selectedObject = selectBuffer[(i * 4) + 3];
      }
    }
    return selectedObject;
  }
  return 0;
}

void Scene::reloadScene() {
  this->reloadSetup();
  this->update();
}

void Scene::reloadSetup() {
  m_program->bind();
  cubeVAO.bind();
  cubesVBO.bind();
  cubesVBO.allocate(864 * this->cubes.size());
  for (int i = 0; i < this->cubes.size(); i++) {
    this->cubes[i].ID = 100 + i;
    auto ptr = cubesVBO.mapRange(864 * i, 864,
                                 QOpenGLBuffer::RangeInvalidate |
                                     QOpenGLBuffer::RangeWrite);
    memcpy(ptr, this->cubes[i].getDots().data(), 864);
    cubesVBO.unmap();
  }
  cubesVBO.release();
  cubeVAO.release();
  m_program->release();
  this->idColors.clear();
  for (int i = 0; i < this->cubes.size(); i++) {
    int r = 2 * i + 100;
    int g = 2 * i + 20;
    int b = 2 * i + 180;
    QVector3D color(r / 255.0f, g / 255.0f, b / 255.0f);
    this->idColors.push_back(color);
  }
}

std::vector<std::vector<Vertex>> Scene::getCoords() {
  std::vector<std::vector<Vertex>> coords(3);
  for (int j = -51; j < 52; j += 2) {
    coords[0].push_back(Vertex(QVector3D(0.0f, float(j), 50.0f)));
    coords[0].push_back(Vertex(QVector3D(0.0f, float(j), -50.0f)));

    coords[0].push_back(Vertex(QVector3D(0.0f, 50.0f, float(j))));
    coords[0].push_back(Vertex(QVector3D(0.0f, -50.0f, float(j))));

    coords[1].push_back(Vertex(QVector3D(float(j), 0.0f, 50.0f)));
    coords[1].push_back(Vertex(QVector3D(float(j), 0.0f, -50.0f)));

    coords[1].push_back(Vertex(QVector3D(0.0f, 50.0f, float(j))));
    coords[1].push_back(Vertex(QVector3D(0.0f, -50.0f, float(j))));

    coords[2].push_back(Vertex(QVector3D(float(j), 50.0f, 0.0f)));
    coords[2].push_back(Vertex(QVector3D(float(j), -50.0f, 0.0f)));

    coords[2].push_back(Vertex(QVector3D(50.0f, float(j), 0.0f)));
    coords[2].push_back(Vertex(QVector3D(-50.0f, float(j), 0.0f)));
  }
  return coords;
}

std::vector<Vertex> Scene::getAxes() {
  std::vector<Vertex> coords;
  coords.push_back(Vertex(QVector3D(50.0f, 0.0f, 0.0f)));
  coords.push_back(Vertex(QVector3D(-50.0f, 0.0f, 0.0f)));
  coords.push_back(Vertex(QVector3D(0.0f, 50.0f, 0.0f)));
  coords.push_back(Vertex(QVector3D(0.0f, -50.0f, 0.0f)));
  coords.push_back(Vertex(QVector3D(0.0f, 0.0f, 50.0f)));
  coords.push_back(Vertex(QVector3D(0.0f, 0.0f, -50.0f)));
  return coords;
}

void Scene::keyPressEvent(QKeyEvent *event) {
  if (event->isAutoRepeat()) {
    event->ignore();
  } else {
    Input::registerKeyPress(event->key());
  }
}

void Scene::keyReleaseEvent(QKeyEvent *event) {
  if (event->isAutoRepeat()) {
    event->ignore();
  } else {
    Input::registerKeyRelease(event->key());
  }
}

void Scene::mousePressEvent(QMouseEvent *event) {
  Input::registerMousePress(event->button());
}

void Scene::mouseReleaseEvent(QMouseEvent *event) {
  Input::registerMouseRelease(event->button());
}

void Scene::rotateX() {}
void Scene::rotateY() {}
void Scene::rotateZ() {}
void Scene::showXYProjection() {}
void Scene::showYZProjection() {}
void Scene::showZXProjection() {}
void Scene::moveLeft() {}
void Scene::moveRight() {}
void Scene::moveDown() {}
void Scene::moveUp() {}
void Scene::moveBackward() {}
void Scene::moveFrontward() {}
