#include "scene.h"
#include "cage.h"
#include <QDebug>
#include <cmath>

#define PI 3.14159265

Scene::Scene() {
  srand(time(NULL));
  collisionsMaster = new CollisionsMaster(cageRadius);
}

void Scene::initializeGL() {
  connect(this, SIGNAL(frameSwapped()), this, SLOT(update()));

  glClearColor(230.0f / 255.0f, 1.0f, 1.0f, 0.0f);
  glClearDepthf(1.0f);
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);
  glLineWidth(5.0f);

  program = new QOpenGLShaderProgram();
  program->addShaderFromSourceFile(QOpenGLShader::Vertex,
                                   ":/shaders/simple.vert");
  program->addShaderFromSourceFile(QOpenGLShader::Fragment,
                                   ":/shaders/simple.frag");
  program->link();
  program->bind();

  color = program->uniformLocation("color");
  position = program->attributeLocation("a_Position");
  normal = program->attributeLocation("a_Normal");
  modelToWorld = program->uniformLocation("modelToWorld");
  worldToCamera = program->uniformLocation("worldToCamera");
  cameraToView = program->uniformLocation("cameraToView");
  lightDir = program->uniformLocation("lightDir");
  lightColor = program->uniformLocation("lightColor");
  specLightColor = program->uniformLocation("speclightColor");
  shine = program->uniformLocation("shine");
  QMatrix4x4 worldToCameraMatrix;
  worldToCameraMatrix.translate(0.0f, 0.0f, -175.0f);
  program->setUniformValue(worldToCamera, worldToCameraMatrix);
  program->setUniformValue(lightDir, QVector3D(1.0f, 1.25f, -2.0f));
  program->setUniformValue(lightColor, QVector3D(0.4f, 0.4f, 0.4f));
  program->setUniformValue(specLightColor, QVector3D(0.7f, 0.7f, 0.7f));
  program->setAttributeValue(shine, 0.2f);

  createBallObjects();
  genStartUp();
  setupSpheres();

  {
    cageVertex.create();
    cageVertex.bind();
    Cage *cage = new Cage(cageRadius);
    cageVertex.setUsagePattern(QOpenGLBuffer::StaticDraw);
    cageVertex.allocate(cage->dots.data(), 12 * 24);
    cageObject.create();
    cageObject.bind();
    program->enableAttributeArray(position);
    program->setAttributeBuffer(position, GL_FLOAT, 0, 3, 0);
    cageObject.release();
    cageVertex.release();
  }

  program->release();
}

void Scene::resizeGL(int w, int h) {
  glViewport(0, 0, w, h);
  projection.setToIdentity();
  projection.perspective(60.0f, w / float(h), 0.2f, 500.0f);
}

void Scene::paintGL() {
  collisionsMaster->handleCollisions(this->balls);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  int nVerticesInOneSphere = 2 * p * (p + 1);

  program->bind();
  program->setUniformValue(cameraToView, projection);

  cageObject.bind();

  program->setUniformValue(color, QVector3D(0.0f, 0.0f, 0.0f));
  program->setUniformValue(modelToWorld, QMatrix4x4());
  glDrawArrays(GL_LINES, 0, 24);

  cageObject.release();

  ballsObject.bind();

  for (int i = 0; i < 3; i++) {
    program->setUniformValue(color, balls[i]->color);
    program->setUniformValue(modelToWorld, balls[i]->toMatrix());
    glDrawArrays(GL_TRIANGLE_STRIP, i * nVerticesInOneSphere,
                 nVerticesInOneSphere);
    balls[i]->translate(balls[i]->direction);
  }

  ballsObject.release();

  program->release();
}

void Scene::update() { QOpenGLWidget::update(); }

void Scene::createBallObjects() {
  Ball *ball1 = new Ball(14);
  ball1->color = QVector3D(1.0f, 51.0f / 255.0f, 0.0f);
  this->balls.push_back(ball1);
  Ball *ball2 = new Ball(12);
  ball2->color = QVector3D(255 / 255.0f, 243 / 255.0f, 33 / 255.0f);
  this->balls.push_back(ball2);
  Ball *ball3 = new Ball(16);
  ball3->color = QVector3D(89 / 255.0f, 247 / 255.0f, 32 / 255.0f);
  this->balls.push_back(ball3);
}

void Scene::genStartUp() {
  this->balls[0]->setTranslation(0, 16.6, 0);
  this->balls[1]->setTranslation(16.6, -16.6, 0);
  this->balls[2]->setTranslation(-16.6, -16.6, 0);
  for (int i = 0; i < 3; i++) {
    this->balls[i]->direction.setX(-50.0f + (float)(rand() % 100));
    this->balls[i]->direction.setY(-50.0f + (float)(rand() % 100));
    this->balls[i]->direction.setZ(-50.0f + (float)(rand() % 100));
    this->balls[i]->direction.normalize();
  }
}

void Scene::restart() { genStartUp(); }

void Scene::setupSpheres() {
  std::vector<float> vertices;
  Ball::insertBall(14, p, vertices);
  Ball::insertBall(12, p, vertices);
  Ball::insertBall(16, p, vertices);
  program->bind();
  this->ballsVertex.create();
  this->ballsVertex.bind();
  this->ballsVertex.setUsagePattern(QOpenGLBuffer::StaticDraw);
  this->ballsVertex.allocate(vertices.data(), vertices.size() * 4);
  this->ballsObject.create();
  this->ballsObject.bind();
  program->enableAttributeArray(position);
  program->setAttributeBuffer(position, GL_FLOAT, 0, 3, 12);
  program->enableAttributeArray(normal);
  program->setAttributeBuffer(normal, GL_FLOAT, 12, 3, 12);
  this->ballsObject.release();
  this->ballsVertex.release();
  program->release();
}

void Scene::setElasticFactor(int factor) {
  this->collisionsMaster->R = factor / 10.0;
}
