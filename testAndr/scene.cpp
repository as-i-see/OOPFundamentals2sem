#include "scene.h"
#include "cage.h"
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <GLES2/gl2platform.h>
#include <QDebug>
#include <cmath>

#define PI 3.14159265

Scene::Scene() {
  srand(time(NULL));
  transform.translate(0.0f, 0.0f, -225.0f);
}

void Scene::initializeGL() {
  connect(this, SIGNAL(frameSwapped()), this, SLOT(update()));
  glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
  glClearDepthf(1.0);
  glDepthFunc(GL_LESS);

  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);

  program = new QOpenGLShaderProgram();
  program->addShaderFromSourceFile(QOpenGLShader::Vertex,
                                   ":/shaders/simple.vert");
  program->addShaderFromSourceFile(QOpenGLShader::Fragment,
                                   ":/shaders/simple.frag");
  program->link();
  program->bind();

  color = program->uniformLocation("color");
  position = program->attributeLocation("a_Position");
  modelToWorld = program->uniformLocation("modelToWorld");
  worldToCamera = program->uniformLocation("worldToCamera");
  cameraToView = program->uniformLocation("cameraToView");

  {
    ballsVertex.create();
    ballsVertex.bind();

    Ball *ball1 = new Ball(5);
    ball1->color = QVector3D(215 / 255.0f, 72 / 255.0f, 29 / 255.0f);
    this->balls.push_back(ball1);
    Ball *ball2 = new Ball(10);
    ball2->color = QVector3D(255 / 255.0f, 243 / 255.0f, 33 / 255.0f);
    this->balls.push_back(ball2);
    Ball *ball3 = new Ball(15);
    ball3->color = QVector3D(89 / 255.0f, 247 / 255.0f, 32 / 255.0f);
    this->balls.push_back(ball3);
    genStartUp();

    std::vector<QVector3D> ballsDots;
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 6480; j++) {
        ballsDots.push_back(this->balls[i]->dots[j]);
      }
    }

    ballsVertex.setUsagePattern(QOpenGLBuffer::StaticDraw);
    ballsVertex.allocate(ballsDots.data(), 3 * 12 * 6480);

    ballsObject.create();
    ballsObject.bind();

    program->enableAttributeArray(position);
    program->setAttributeBuffer(position, GL_FLOAT, 0, 3, 0);

    ballsObject.release();
    ballsVertex.release();
  }
  {
    cageVertex.create();
    cageVertex.bind();
    Cage *cage = new Cage();
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
  projection.setToIdentity();
  projection.perspective(45.0f, w / float(h), 0.0f, 1000.0f);
}

void Scene::paintGL() {
  handleCollisions();
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLineWidth(10.0f);

  QVector3D b1tr = this->balls[0]->transform.translation();
  renderSphere(b1tr.x(), b1tr.y(), b1tr.z(), balls[0]->radius, 80,
               balls[0]->color);
  balls[0]->transform.translate(balls[0]->direction);
  QVector3D b2tr = this->balls[1]->transform.translation();
  renderSphere(b2tr.x(), b2tr.y(), b2tr.z(), balls[1]->radius, 80,
               balls[1]->color);
  balls[1]->transform.translate(balls[1]->direction);
  QVector3D b3tr = this->balls[2]->transform.translation();
  renderSphere(b3tr.x(), b3tr.y(), b3tr.z(), balls[2]->radius, 80,
               balls[2]->color);
  balls[2]->transform.translate(balls[2]->direction);
  //  ballsObject.bind();
  //  program->setUniformValue(cameraToView, projection);
  //  program->setUniformValue(worldToCamera, transform.toMatrix());

  //  for (int i = 0; i < 3; i++) {
  //    program->setUniformValue(color, this->balls[i]->color);
  //    program->setUniformValue(modelToWorld,
  //                             this->balls[i]->transform.toMatrix());
  //    glDrawArrays(GL_LINE_STRIP, 6480 * i, 6480);
  //    this->balls[i]->transform.translate(this->balls[i]->direction);
  //  }
  //  ballsObject.release();
  program->bind();
  {
    cageObject.bind();
    program->setUniformValue(cameraToView, projection);
    program->setUniformValue(worldToCamera, transform.toMatrix());
    program->setUniformValue(color, QVector3D(0.0f, 0.0f, 0.0f));
    program->setUniformValue(modelToWorld, QMatrix4x4());
    glDrawArrays(GL_LINES, 0, 24);
    cageObject.release();
  }
  program->release();
}

void Scene::update() { QOpenGLWidget::update(); }

void Scene::genStartUp() {
  this->balls[0]->transform.setTranslation(0, 16.6, 0);
  this->balls[1]->transform.setTranslation(16.6, -16.6, 0);
  this->balls[2]->transform.setTranslation(-16.6, -16.6, 0);
  for (int i = 0; i < 3; i++) {
    this->balls[i]->direction.setX(-50.0f + (float)(rand() % 100));
    this->balls[i]->direction.setY(-50.0f + (float)(rand() % 100));
    this->balls[i]->direction.setZ(-50.0f + (float)(rand() % 100));
    this->balls[i]->direction.normalize();
  }
}

void Scene::start() { genStartUp(); }

void Scene::handleCollisions() {
  auto collisions = collisionsOccured();
  for (auto collision : collisions) {
    if (collision.second < 6) {
      Ball *ball = this->balls[collision.first - 6];
      int plane = collision.second;
      switch (plane) {
      case 0:
      case 3:
        ball->direction.setY(ball->direction.y() * (-1));
        break;
      case 1:
      case 2:
        ball->direction.setX(ball->direction.x() * (-1));
        break;
      case 4:
      case 5:
        ball->direction.setZ(ball->direction.z() * (-1));
        break;
      }
    } else {
      resolveBallsCollision(collision.first, collision.second);
    }
  }
}

std::vector<std::pair<int, int>> Scene::collisionsOccured() {

  std::vector<std::pair<int, int>> collisions;
  std::vector<QVector3D> centers = {
      this->balls[0]->transform.toMatrix() * QVector3D(0, 0, 0),
      this->balls[1]->transform.toMatrix() * QVector3D(0, 0, 0),
      this->balls[2]->transform.toMatrix() * QVector3D(0, 0, 0)};
  QVector3D FTL(-50, 50, -50);
  QVector3D FBL(-50, -50, -50);
  QVector3D FBR(50, -50, -50);
  QVector3D FTR(50, 50, -50);
  QVector3D BTL(-50, 50, 50);
  QVector3D BBL(-50, -50, 50);
  QVector3D BBR(50, -50, 50);
  QVector3D BTR(50, 50, 50);

  for (int i = 0; i < 3; i++) {
    float dist0 = (float)fabs(centers[i].distanceToPlane(FTL, BTL, BTR));
    if (dist0 <= this->balls[i]->radius)
      collisions.push_back({6 + i, 0});
    float dist1 = (float)fabs(centers[i].distanceToPlane(FTR, BBR, BTR));
    if (dist1 <= this->balls[i]->radius)
      collisions.push_back({6 + i, 1});
    float dist2 = (float)fabs(centers[i].distanceToPlane(FTL, BTL, BBL));
    if (dist2 <= this->balls[i]->radius)
      collisions.push_back({6 + i, 2});
    float dist3 = (float)fabs(centers[i].distanceToPlane(FBL, BBL, BBR));
    if (dist3 <= this->balls[i]->radius)
      collisions.push_back({6 + i, 3});
    float dist4 = (float)fabs(centers[i].distanceToPlane(FTL, FTR, FBR));
    if (dist4 <= this->balls[i]->radius)
      collisions.push_back({6 + i, 4});
    float dist5 = (float)fabs(centers[i].distanceToPlane(BTL, BTR, BBR));
    if (dist5 <= this->balls[i]->radius)
      collisions.push_back({6 + i, 5});
  }

  float dist67 = centers[0].distanceToPoint(centers[1]);
  if (dist67 <= this->balls[0]->radius + this->balls[1]->radius)
    collisions.push_back({6, 7});

  float dist68 = centers[0].distanceToPoint(centers[2]);
  if (dist68 <= this->balls[0]->radius + this->balls[2]->radius)
    collisions.push_back({6, 8});

  float dist78 = centers[1].distanceToPoint(centers[2]);
  if (dist78 <= this->balls[1]->radius + this->balls[2]->radius)
    collisions.push_back({7, 8});

  return collisions;
}

void Scene::resolveBallsCollision(int bi1, int bi2) {
  QVector3D center(0.0, 0.0, 0.0);
  Ball *b1 = this->balls[bi1 - 6];
  Ball *b2 = this->balls[bi2 - 6];
  QVector3D c1 = b1->transform.toMatrix() * center;
  QVector3D c2 = b2->transform.toMatrix() * center;

  /// **************************
  ///   initialize some variables
  double r12 = b1->radius + b2->radius;
  double m1 = b1->radius;
  double m2 = b2->radius;
  double vx1 = b1->direction.x();
  double vy1 = b1->direction.y();
  double vz1 = b1->direction.z();
  double vx2 = b2->direction.x();
  double vy2 = b2->direction.y();
  double vz2 = b2->direction.z();

  double m21 = m2 / m1;
  double x21 = c2.x() - c1.x();
  double y21 = c2.y() - c1.y();
  double z21 = c2.z() - c1.z();
  double vx21 = vx2 - vx1;
  double vy21 = vy2 - vy1;
  double vz21 = vz2 - vz1;
  double vx_cm = (m1 * vx1 + m2 * vx2) / (m1 + m2);
  double vy_cm = (m1 * vy1 + m2 * vy2) / (m1 + m2);
  double vz_cm = (m1 * vz1 + m2 * vz2) / (m1 + m2);

  double theta2, phi2, st, ct, sp, cp, vx1r, vy1r, vz1r, fvz1r, thetav, phiv,
      dr, alpha, beta, sbeta, cbeta, dc, sqs, t, a, dvz2, vx2r, vy2r, vz2r;

  /// **************************
  ///   calculate relative distance and relative speed ***
  double d = sqrt(x21 * x21 + y21 * y21 + z21 * z21);
  double v = sqrt(vx21 * vx21 + vy21 * vy21 + vz21 * vz21);

  /// **************************
  ///   return if relative speed = 0
  if (v == 0)
    return;

  /// **************************
  ///   shift coordinate system so that ball 1 is at the origin
  b2->transform.setTranslation(x21, y21, z21);
  c2 = b2->transform.toMatrix() * center;

  /// **************************
  ///   boost coordinate system so that ball 2 is resting
  b1->direction = QVector3D(-vx21, -vy21, -vz21);
  vx1 = b1->direction.x();
  vy1 = b1->direction.y();
  vz1 = b1->direction.z();

  /// **************************
  ///   find the polar coordinates of the location of ball 2
  theta2 = acos(c2.z() / d);
  if (c2.x() == 0 && c2.y() == 0) {
    phi2 = 0;
  } else {
    phi2 = atan2(c2.y(), c2.x());
  }
  st = sin(theta2);
  ct = cos(theta2);
  sp = sin(phi2);
  cp = cos(phi2);

  /// **************************
  ///   express the velocity vector of ball 1 in a rotated coordinate
  ///          system where ball 2 lies on the z-axis
  vx1r = ct * cp * vx1 + ct * sp * vy1 - st * vz1;
  vy1r = cp * vy1 - sp * vx1;
  vz1r = st * cp * vx1 + st * sp * vy1 + ct * vz1;
  fvz1r = vz1r / v;
  if (fvz1r > 1) {
    fvz1r = 1;
  } // fix for possible rounding errors
  else if (fvz1r < -1) {
    fvz1r = -1;
  }
  thetav = acos(fvz1r);
  if (vx1r == 0 && vy1r == 0) {
    phiv = 0;
  } else {
    phiv = atan2(vy1r, vx1r);
  }

  /// **************************
  ///   calculate the normalized impact parameter
  dr = d * sin(thetav) / r12;

  /// **************************
  ///   calculate impact angles
  alpha = asin(-dr);
  beta = phiv;
  sbeta = sin(beta);
  cbeta = cos(beta);

  /// **************************
  ///   update positions and reverse the coordinate shift ATTENTION
  b2->transform.setTranslation(c2.x() + c1.x(), c2.y() + c1.y(),
                               c2.z() + c1.z());

  /// **************************
  ///   update velocities
  a = tan(thetav + alpha);

  dvz2 = 2 * (vz1r + a * (cbeta * vx1r + sbeta * vy1r)) /
         ((1 + a * a) * (1 + m21));

  vz2r = dvz2;
  vx2r = a * cbeta * dvz2;
  vy2r = a * sbeta * dvz2;
  vz1r = vz1r - m21 * vz2r;
  vx1r = vx1r - m21 * vx2r;
  vy1r = vy1r - m21 * vy2r;
  /// **************************
  ///   rotate the velocity vectors back and add the initial velocity
  ///           vector of ball 2 to retrieve the original coordinate system
  b1->direction = QVector3D((ct * cp * vx1r - sp * vy1r + st * cp * vz1r + vx2),
                            (ct * sp * vx1r + cp * vy1r + st * sp * vz1r + vy2),
                            (ct * vz1r - st * vx1r + vz2));
  b2->direction = QVector3D((ct * cp * vx2r - sp * vy2r + st * cp * vz2r + vx2),
                            (ct * sp * vx2r + cp * vy2r + st * sp * vz2r + vy2),
                            (ct * vz2r - st * vx2r + vz2));

  /// **************************
  ///   velocity correction for inelastic collisions
  double R = 0.75;
  b1->direction = QVector3D(((b1->direction.x() - vx_cm) * R + vx_cm),
                            ((b1->direction.y() - vy_cm) * R + vy_cm),
                            ((b1->direction.z() - vz_cm) * R + vz_cm));
  b2->direction = QVector3D(((b2->direction.x() - vx_cm) * R + vx_cm),
                            ((b2->direction.y() - vy_cm) * R + vy_cm),
                            ((b2->direction.z() - vz_cm) * R + vz_cm));
}

void Scene::renderSphere(float cx, float cy, float cz, float r, int p,
                         QVector3D ballColor) {
  float theta1 = 0.0, theta2 = 0.0, theta3 = 0.0;
  float ex = 0.0f, ey = 0.0f, ez = 0.0f;
  float px = 0.0f, py = 0.0f, pz = 0.0f;
  GLfloat /*vertices[p * 6 + 6], */ normals[p * 6 + 6], texCoords[p * 4 + 4];
  std::vector<float> vertices;

  if (r < 0)
    r = -r;

  if (p < 0)
    p = -p;

  for (int i = 0; i < p / 2; ++i) {
    theta1 = i * (M_PI * 2) / p - M_PI_2;
    theta2 = (i + 1) * (M_PI * 2) / p - M_PI_2;

    for (int j = 0; j <= p; ++j) {
      theta3 = j * (M_PI * 2) / p;

      ex = cosf(theta2) * cosf(theta3);
      ey = sinf(theta2);
      ez = cosf(theta2) * sinf(theta3);
      px = cx + r * ex;
      py = cy + r * ey;
      pz = cz + r * ez;

      //      vertices[((6 * j) + (0 % 6))] = px;
      //      vertices[(6 * j) + (1 % 6)] = py;
      //      vertices[(6 * j) + (2 % 6)] = pz;
      vertices.push_back(px);
      vertices.push_back(py);
      vertices.push_back(pz);

      normals[(6 * j) + (0 % 6)] = ex;
      normals[(6 * j) + (1 % 6)] = ey;
      normals[(6 * j) + (2 % 6)] = ez;

      texCoords[(4 * j) + (0 % 4)] = -(j / (float)p);
      texCoords[(4 * j) + (1 % 4)] = 2 * (i + 1) / (float)p;

      ex = cosf(theta1) * cosf(theta3);
      ey = sinf(theta1);
      ez = cosf(theta1) * sinf(theta3);
      px = cx + r * ex;
      py = cy + r * ey;
      pz = cz + r * ez;

      //      vertices[(6 * j) + (3 % 6)] = px;
      //      vertices[(6 * j) + (4 % 6)] = py;
      //      vertices[(6 * j) + (5 % 6)] = pz;
      vertices.push_back(px);
      vertices.push_back(py);
      vertices.push_back(pz);

      normals[(6 * j) + (3 % 6)] = ex;
      normals[(6 * j) + (4 % 6)] = ey;
      normals[(6 * j) + (5 % 6)] = ez;

      texCoords[(4 * j) + (2 % 4)] = -(j / (float)p);
      texCoords[(4 * j) + (3 % 4)] = 2 * i / (float)p;
    }
  }
  program->bind();
  QOpenGLBuffer b;
  b.create();
  b.bind();
  b.setUsagePattern(QOpenGLBuffer::StaticDraw);
  b.allocate(vertices.data(), (p / 2) * (p + 1) * 6 * 4);
  QOpenGLVertexArrayObject o;
  o.create();
  o.bind();
  program->enableAttributeArray(position);
  program->setAttributeBuffer(position, GL_FLOAT, 0, 3, 0);

  program->setUniformValue(cameraToView, projection);
  program->setUniformValue(worldToCamera, transform.toMatrix());
  program->setUniformValue(color, ballColor);
  program->setUniformValue(modelToWorld, QMatrix4x4());
  o.release();
  b.release();
  o.bind();
  glDrawArrays(GL_TRIANGLE_STRIP, 0, (p / 2) * (p + 1) * 2);
  o.release();
  program->release();
}
