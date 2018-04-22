#include "scene.h"
#include "GL/GLU.h"
#include "cube.h"
#include "input.h"
#include "vertex.h"
#include <QColor>
#include <QDebug>
#include <QMatrix4x4>
#include <QOpenGLShaderProgram>
#include <QPoint>
#include <QQuaternion>
#include <QScreen>
#include <QString>
#include <QSurfaceFormat>
#include <algorithm>

Scene::Scene(QWidget *parent) : QOpenGLWidget(parent) {
  QSurfaceFormat format;
  format.setDepthBufferSize(24);
  format.setSwapBehavior(QSurfaceFormat::DoubleBuffer);
  setFormat(format);
  // m_transform.translate(0.0f, 0.0f, -5.0f);
  this->colorDialog = new QColorDialog(this);
  connect(this->colorDialog, SIGNAL(colorSelected(QColor)), this,
          SLOT(changeColor(QColor)));
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
    if (this->cubes[i].isSelected())
      m_program->setUniformValue(u_figureColor, this->selectionColor);
    else
      m_program->setUniformValue(u_figureColor, this->cubes[i].getColor());
    m_program->setUniformValue(u_modelToWorld,
                               this->cubes[i].transform.toMatrix());
    glDrawArrays(GL_TRIANGLES, 36 * i, 36);
  }
  cubeVAO.release();

  m_program->release();

  QMatrix4x4 projectionMatrix = this->m_projection * m_camera.toMatrix();
  glMatrixMode(GL_PROJECTION);
  glLoadMatrixf(projectionMatrix.data());
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  for (int i = 0; i < this->prisms.size(); i++) {
    this->prisms[i].draw();
  }
  if (this->showXY) {
    for (int i = 0; i < this->prisms.size(); i++) {
      this->prisms[i].drawXYProjection();
    }
  }
  if (this->showYZ) {
    for (int i = 0; i < this->prisms.size(); i++) {
      this->prisms[i].drawYZProjection();
    }
  }
  if (this->showXZ) {
    for (int i = 0; i < this->prisms.size(); i++) {
      this->prisms[i].drawXZProjection();
    }
  }
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
    if (selectedObjectID) {
      if (selectedObjectID % 2) {
        int ID = (selectedObjectID - 1) / 2;
        if (this->cubes[ID].isSelected()) {
          this->cubes[ID].setSelected(false);
          auto pos = std::find(this->selectedCubes.begin(),
                               this->selectedCubes.end(), ID);
          this->selectedCubes.erase(pos);
        } else {
          this->cubes[ID].setSelected(true);
          this->selectedCubes.push_back(ID);
        }
      } else {
        int ID = (selectedObjectID - 2) / 2;
        if (this->prisms[ID].isSelected()) {
          this->prisms[ID].setSelected(false);
          auto pos = std::find(this->selectedPrisms.begin(),
                               this->selectedPrisms.end(), ID);
          this->selectedPrisms.erase(pos);
        } else {
          this->prisms[ID].setSelected(true);
          this->selectedPrisms.push_back(ID);
        }
      }
    }
    Input::registerMouseRelease(Qt::LeftButton);
  }

  QOpenGLWidget::update();
}

int Scene::retrieveObjectID(int x, int y) {

  int objectsFound = 0;
  int viewportCoords[4] = {0};

  unsigned int selectBuffer[100] = {0};

  glSelectBuffer(100, selectBuffer);

  glViewport(0, 0, w, h);
  glGetIntegerv(GL_VIEWPORT, viewportCoords);

  glMatrixMode(GL_PROJECTION);
  glPushMatrix();

  glRenderMode(GL_SELECT);
  glLoadIdentity();

  gluPickMatrix(x, y, 1, 1, viewportCoords);
  gluPerspective(45.0, (float)w / (float)h, 0.01, 200.0);
  QVector3D pos = m_camera.translation();
  QVector3D view = m_camera.forward();
  QVector3D up = m_camera.up();

  gluLookAt(pos.x(), pos.y(), pos.z(), pos.x() + view.x(), pos.y() + view.y(),
            pos.z() + view.z(), up.x(), up.y(), up.z());
  glMatrixMode(GL_MODELVIEW);

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glLoadIdentity();

  glInitNames();
  for (int i = 0; i < this->cubes.size(); i++) {
    glPushName(this->cubes[i].ID);
    glPushMatrix();
    glLoadMatrixf(this->cubes[i].transform.toMatrix().data());
    for (int j = 0; j < 12; j++) {
      glBegin(GL_TRIANGLES);
      glVertex3f(this->cubes[i].getDots()[3 * j].position().x(),
                 this->cubes[i].getDots()[3 * j].position().y(),
                 this->cubes[i].getDots()[3 * j].position().z());
      glVertex3f(this->cubes[i].getDots()[3 * j + 1].position().x(),
                 this->cubes[i].getDots()[3 * j + 1].position().y(),
                 this->cubes[i].getDots()[3 * j + 1].position().z());
      glVertex3f(this->cubes[i].getDots()[3 * j + 2].position().x(),
                 this->cubes[i].getDots()[3 * j + 2].position().y(),
                 this->cubes[i].getDots()[3 * j + 2].position().z());
      glEnd();
    }
    glPopMatrix();
    glPopName();
  }
  for (int i = 0; i < this->prisms.size(); i++) {
    glPushName(this->prisms[i].ID);
    this->prisms[i].draw();
    glPopName();
  }

  objectsFound = glRenderMode(GL_RENDER);
  glMatrixMode(GL_PROJECTION);
  glPopMatrix();
  glMatrixMode(GL_MODELVIEW);

  if (objectsFound > 0) {
    unsigned int lowestDepth = selectBuffer[1];
    int selectedObject = selectBuffer[3];
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
  this->selectedCubes.clear();
  this->selectedPrisms.clear();
  m_program->bind();
  cubeVAO.bind();
  cubesVBO.bind();
  cubesVBO.allocate(864 * this->cubes.size());
  for (int i = 0; i < this->cubes.size(); i++) {
    this->cubes[i].ID = 2 * i + 1;
    this->cubes[i].setSelected(false);
    auto ptr = cubesVBO.mapRange(864 * i, 864,
                                 QOpenGLBuffer::RangeInvalidate |
                                     QOpenGLBuffer::RangeWrite);
    memcpy(ptr, this->cubes[i].getDots().data(), 864);
    cubesVBO.unmap();
  }
  cubesVBO.release();
  cubeVAO.release();
  m_program->release();
  for (int i = 0; i < this->prisms.size(); i++) {
    this->prisms[i].ID = 2 * i + 2;
    this->prisms[i].setSelected(false);
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

void Scene::rotateX() {
  if (this->selectedCubes.empty())
    return;
  QQuaternion xRotation =
      QQuaternion::fromAxisAndAngle(10.0f, 0.0f, 0.0f, this->rotationAngle);
  for (int i = 0; i < this->selectedCubes.size(); i++) {
    int ID = this->selectedCubes[i];
    this->cubes[ID].transform.rotate(xRotation);
  }
}
void Scene::rotateY() {}
void Scene::rotateZ() {}
void Scene::showXYProjection() {
  if (this->showXY)
    this->showXY = false;
  else
    this->showXY = true;
}
void Scene::showYZProjection() {
  if (this->showYZ)
    this->showYZ = false;
  else
    this->showYZ = true;
}

void Scene::showXZProjection() {
  if (this->showXZ)
    this->showXZ = false;
  else
    this->showXZ = true;
}
void Scene::moveXPos() {
  for (auto ID : this->selectedCubes) {
    this->cubes[ID].transform.translate(1.0f, 0.0f, 0.0f);
  }
  for (auto ID : this->selectedPrisms) {
    this->prisms[ID].transform.translate(1.0f, 0.0f, 0.0f);
  }
}
void Scene::moveXNeg() {
  for (auto ID : this->selectedCubes) {
    this->cubes[ID].transform.translate(-1.0f, 0.0f, 0.0f);
  }
  for (auto ID : this->selectedPrisms) {
    this->prisms[ID].transform.translate(-1.0f, 0.0f, 0.0f);
  }
}
void Scene::moveYPos() {
  for (auto ID : this->selectedCubes) {
    this->cubes[ID].transform.translate(0.0f, 1.0f, 0.0f);
  }
  for (auto ID : this->selectedPrisms) {
    this->prisms[ID].transform.translate(0.0f, 1.0f, 0.0f);
  }
}
void Scene::moveYNeg() {
  for (auto ID : this->selectedCubes) {
    this->cubes[ID].transform.translate(0.0f, -1.0f, 0.0f);
  }
  for (auto ID : this->selectedPrisms) {
    this->prisms[ID].transform.translate(0.0f, -1.0f, 0.0f);
  }
}
void Scene::moveZPos() {
  for (auto ID : this->selectedCubes) {
    this->cubes[ID].transform.translate(0.0f, 0.0f, 1.0f);
  }
  for (auto ID : this->selectedPrisms) {
    this->prisms[ID].transform.translate(0.0f, 0.0f, 1.0f);
  }
}
void Scene::moveZNeg() {
  for (auto ID : this->selectedCubes) {
    this->cubes[ID].transform.translate(0.0f, 0.0f, -1.0f);
  }
  for (auto ID : this->selectedPrisms) {
    this->prisms[ID].transform.translate(0.0f, 0.0f, -1.0f);
  }
}

void Scene::changeColor(QColor color) {
  QVector3D glColor(color.red() / 255.0f, color.green() / 255.0f,
                    color.blue() / 255.0f);
  for (auto ID : this->selectedCubes) {
    this->cubes[ID].setColor(glColor);
  }
  for (auto ID : this->selectedPrisms) {
    this->prisms[ID].setColor(glColor);
  }
}
