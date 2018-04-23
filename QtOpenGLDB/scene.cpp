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
  this->colorDialog = new QColorDialog(this);
  connect(this->colorDialog, SIGNAL(colorSelected(QColor)), this,
          SLOT(changeColor(QColor)));
  coordAxes = getCoordAxes();
}

void Scene::initializeGL() {
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  connect(this, SIGNAL(frameSwapped()), this, SLOT(update()));
  glEnable(GL_DEPTH_TEST);
  glClearDepth(1.0f);
  glDepthFunc(GL_LESS);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_COLOR_MATERIAL);
  glEnable(GL_POINT_SMOOTH);
  glShadeModel(GL_SMOOTH);
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

  QMatrix4x4 projectionMatrix = this->m_projection * m_camera.toMatrix();
  glMatrixMode(GL_PROJECTION);
  glLoadMatrixf(projectionMatrix.data());
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glLightfv(GL_LIGHT0, GL_POSITION, g_LightPosition);
  drawCoordAxes();
  for (int i = 0; i < this->cubes.size(); i++) {
    this->cubes[i].draw();
  }
  for (int i = 0; i < this->prisms.size(); i++) {
    this->prisms[i].draw();
  }
  if (this->showXY) {
    for (int i = 0; i < this->prisms.size(); i++) {
      this->prisms[i].drawXYProjection();
    }
    for (int i = 0; i < this->cubes.size(); i++) {
      this->cubes[i].drawXYProjection();
    }
  }
  if (this->showYZ) {
    for (int i = 0; i < this->prisms.size(); i++) {
      this->prisms[i].drawYZProjection();
    }
    for (int i = 0; i < this->cubes.size(); i++) {
      this->cubes[i].drawYZProjection();
    }
  }
  if (this->showXZ) {
    for (int i = 0; i < this->prisms.size(); i++) {
      this->prisms[i].drawXZProjection();
    }
    for (int i = 0; i < this->cubes.size(); i++) {
      this->cubes[i].drawXZProjection();
    }
  }
}

void Scene::drawCoordAxes() {
  glLineWidth(0.1f);
  for (int i = 0; i < 3; i++) {
    glColor3f(this->coordsColors[i].x(), this->coordsColors[i].y(),
              this->coordsColors[i].z());
    for (int j = 0; j < 104; j++) {
      glBegin(GL_LINES);
      glVertex3f(this->coordAxes[208 * i + 2 * j].position().x(),
                 this->coordAxes[208 * i + 2 * j].position().y(),
                 this->coordAxes[208 * i + 2 * j].position().z());
      glVertex3f(this->coordAxes[208 * i + 2 * j + 1].position().x(),
                 this->coordAxes[208 * i + 2 * j + 1].position().y(),
                 this->coordAxes[208 * i + 2 * j + 1].position().z());
      glEnd();
    }
  }
  glLineWidth(2.5f);
  glColor3f(this->whiteColor.x(), this->whiteColor.y(), this->whiteColor.z());
  for (int i = 0; i < 3; i++) {
    glBegin(GL_LINES);
    glVertex3f(this->coordAxes[624 + 2 * i].position().x(),
               this->coordAxes[624 + 2 * i].position().y(),
               this->coordAxes[624 + 2 * i].position().z());
    glVertex3f(this->coordAxes[624 + 2 * i + 1].position().x(),
               this->coordAxes[624 + 2 * i + 1].position().y(),
               this->coordAxes[624 + 2 * i + 1].position().z());
    glEnd();
  }
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
    this->cubes[i].draw();
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

std::vector<Vertex> Scene::getCoordAxes() {
  std::vector<Vertex> coords;
  for (int j = -51; j < 52; j += 2) {
    coords.push_back(Vertex(QVector3D(0.0f, float(j), 50.0f)));
    coords.push_back(Vertex(QVector3D(0.0f, float(j), -50.0f)));

    coords.push_back(Vertex(QVector3D(0.0f, 50.0f, float(j))));
    coords.push_back(Vertex(QVector3D(0.0f, -50.0f, float(j))));
  }
  for (int j = -51; j < 52; j += 2) {
    coords.push_back(Vertex(QVector3D(float(j), 0.0f, 50.0f)));
    coords.push_back(Vertex(QVector3D(float(j), 0.0f, -50.0f)));

    coords.push_back(Vertex(QVector3D(50.0f, 0.0f, float(j))));
    coords.push_back(Vertex(QVector3D(-50.0f, 0.0f, float(j))));
  }
  for (int j = -51; j < 52; j += 2) {
    coords.push_back(Vertex(QVector3D(float(j), 50.0f, 0.0f)));
    coords.push_back(Vertex(QVector3D(float(j), -50.0f, 0.0f)));

    coords.push_back(Vertex(QVector3D(50.0f, float(j), 0.0f)));
    coords.push_back(Vertex(QVector3D(-50.0f, float(j), 0.0f)));
  }
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
  QQuaternion xRotation =
      QQuaternion::fromAxisAndAngle(1.0f, 0.0f, 0.0f, this->rotationAngle);
  for (int i = 0; i < this->selectedCubes.size(); i++) {
    int ID = this->selectedCubes[i];
    this->cubes[ID].transform.rotate(xRotation);
  }
  for (int i = 0; i < this->selectedPrisms.size(); i++) {
    int ID = this->selectedPrisms[i];
    this->prisms[ID].transform.rotate(xRotation);
  }
}

void Scene::rotateY() {
  QQuaternion yRotation =
      QQuaternion::fromAxisAndAngle(0.0f, 1.0f, 0.0f, this->rotationAngle);
  for (int i = 0; i < this->selectedCubes.size(); i++) {
    int ID = this->selectedCubes[i];
    this->cubes[ID].transform.rotate(yRotation);
  }
  for (int i = 0; i < this->selectedPrisms.size(); i++) {
    int ID = this->selectedPrisms[i];
    this->prisms[ID].transform.rotate(yRotation);
  }
}

void Scene::rotateZ() {
  QQuaternion zRotation =
      QQuaternion::fromAxisAndAngle(0.0f, 0.0f, 1.0f, this->rotationAngle);
  for (int i = 0; i < this->selectedCubes.size(); i++) {
    int ID = this->selectedCubes[i];
    this->cubes[ID].transform.rotate(zRotation);
  }
  for (int i = 0; i < this->selectedPrisms.size(); i++) {
    int ID = this->selectedPrisms[i];
    this->prisms[ID].transform.rotate(zRotation);
  }
}

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
    this->cubes[ID].transform.translate(1.0f * translationUnit, 0.0f, 0.0f);
  }
  for (auto ID : this->selectedPrisms) {
    this->prisms[ID].transform.translate(1.0f * translationUnit, 0.0f, 0.0f);
  }
}

void Scene::moveXNeg() {
  for (auto ID : this->selectedCubes) {
    this->cubes[ID].transform.translate(-1.0f * translationUnit, 0.0f, 0.0f);
  }
  for (auto ID : this->selectedPrisms) {
    this->prisms[ID].transform.translate(-1.0f * translationUnit, 0.0f, 0.0f);
  }
}
void Scene::moveYPos() {
  for (auto ID : this->selectedCubes) {
    this->cubes[ID].transform.translate(0.0f, 1.0f * translationUnit, 0.0f);
  }
  for (auto ID : this->selectedPrisms) {
    this->prisms[ID].transform.translate(0.0f, 1.0f * translationUnit, 0.0f);
  }
}
void Scene::moveYNeg() {
  for (auto ID : this->selectedCubes) {
    this->cubes[ID].transform.translate(0.0f, -1.0f * translationUnit, 0.0f);
  }
  for (auto ID : this->selectedPrisms) {
    this->prisms[ID].transform.translate(0.0f, -1.0f * translationUnit, 0.0f);
  }
}
void Scene::moveZPos() {
  for (auto ID : this->selectedCubes) {
    this->cubes[ID].transform.translate(0.0f, 0.0f, 1.0f * translationUnit);
  }
  for (auto ID : this->selectedPrisms) {
    this->prisms[ID].transform.translate(0.0f, 0.0f, 1.0f * translationUnit);
  }
}
void Scene::moveZNeg() {
  for (auto ID : this->selectedCubes) {
    this->cubes[ID].transform.translate(0.0f, 0.0f, -1.0f * translationUnit);
  }
  for (auto ID : this->selectedPrisms) {
    this->prisms[ID].transform.translate(0.0f, 0.0f, -1.0f * translationUnit);
  }
}

void Scene::scale() {
  for (auto ID : this->selectedCubes) {
    this->cubes[ID].transform.scale(this->scalingFactor);
  }
  for (auto ID : this->selectedPrisms) {
    this->prisms[ID].transform.scale(this->scalingFactor);
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

void Scene::loadScene(
    std::pair<std::vector<Cube>, std::vector<Prism>> figures) {
  this->cubes = figures.first;
  this->prisms = figures.second;
  this->selectedCubes.clear();
  this->selectedPrisms.clear();
  for (int i = 0; i < this->cubes.size(); i++) {
    this->cubes[i].ID = 2 * i + 1;
    this->cubes[i].setSelected(false);
    this->cubes[i].transform.centreOfMass = this->cubes[i].centreOfMass();
  }
  for (int i = 0; i < this->prisms.size(); i++) {
    this->prisms[i].ID = 2 * i + 2;
    this->prisms[i].setSelected(false);
    this->prisms[i].transform.centreOfMass = this->prisms[i].centreOfMass();
  }
  QOpenGLWidget::update();
}

void Scene::sceneConfigRequest(
    std::pair<std::vector<Cube>, std::vector<Prism>> &config) {
  config.first = this->cubes;
  config.second = this->prisms;
}

void Scene::setPreferences(std::vector<float> prefs) {
  this->rotationAngle = prefs[0];
  this->translationUnit = prefs[1];
  this->scalingFactor = prefs[2];
}
