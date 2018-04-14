#include "scene.h"
#include <QString>
#include <QOpenGLShaderProgram>
#include "vertex.h"
#include "input.h"
#include <QDebug>

Scene::Scene(QWidget* parent) : QOpenGLWidget(parent)
{
    this->setFocusPolicy(Qt::ClickFocus);
    m_transform.translate(0.0f, 0.0f, -5.0f);
}

void Scene::initializeGL() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    connect(this, SIGNAL(frameSwapped()), this, SLOT(update()));
    glEnable(GL_CULL_FACE);
    glLineWidth(0.1f);

    m_program = new QOpenGLShaderProgram();
    m_program->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/simple.vert");
    m_program->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/simple.frag");
    m_program->link();
    m_program->bind();

    /////////////////////////////////

    cubeVAO.create();
    cubeVAO.bind();

    u_modelToWorld = m_program->uniformLocation("modelToWorld");
    u_worldToCamera = m_program->uniformLocation("worldToCamera");
    u_cameraToView = m_program->uniformLocation("cameraToView");

    cubesVBO.create();
    cubesVBO.setUsagePattern(QOpenGLBuffer::DynamicDraw);
    cubesVBO.bind();

    m_program->enableAttributeArray(0);
    m_program->enableAttributeArray(1);
    m_program->setAttributeBuffer(0, GL_FLOAT, 0, 3, 24);
    m_program->setAttributeBuffer(1, GL_FLOAT, 12, 3, 24);

    cubesVBO.release();
    cubeVAO.release();

    //////////////////////////////////

    coordsVAO.create();
    coordsVAO.bind();

    coordsVBO.create();
    coordsVBO.setUsagePattern(QOpenGLBuffer::StaticDraw);
    coordsVBO.bind();

    m_program->enableAttributeArray(0);
    m_program->enableAttributeArray(1);
    m_program->setAttributeBuffer(0, GL_FLOAT, 0, 3, 24);
    m_program->setAttributeBuffer(1, GL_FLOAT, 12, 3, 24);

    coordsVBO.allocate(15120);
    auto coordsVec = getCoords();
    for (unsigned i = 0 ; i < 3; i++) {
        auto ptr = coordsVBO.mapRange(i * 4992, 4992, QOpenGLBuffer::RangeInvalidate | QOpenGLBuffer::RangeWrite);
        memcpy(ptr, coordsVec[i].data(), 4992);
        coordsVBO.unmap();
    }
    auto axesVec = getAxes();
    auto ptr = coordsVBO.mapRange(14976, 144, QOpenGLBuffer::RangeInvalidate | QOpenGLBuffer::RangeWrite);
    memcpy(ptr, axesVec.data(), 144);
    coordsVBO.unmap();

    coordsVBO.release();
    coordsVAO.release();

    m_program->release();
}

void Scene::resizeGL(int w, int h) {
    m_projection.setToIdentity();
    m_projection.perspective(45.0f, w / float(h), 0.0f, 1000.0f);
}

void Scene::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLineWidth(0.1f);
    m_program->bind();

    coordsVAO.bind();
    m_program->setUniformValue(u_cameraToView, m_projection);
    m_program->setUniformValue(u_worldToCamera, m_camera.toMatrix());
    m_program->setUniformValue(u_modelToWorld, m_transform.toMatrix()); // yeah
    glDrawArrays(GL_LINES, 0, 624);
    glLineWidth(2.0f);
    glDrawArrays(GL_LINES, 624, 630);
    coordsVAO.release();

    cubeVAO.bind();
    m_program->setUniformValue(u_cameraToView, m_projection);
    m_program->setUniformValue(u_worldToCamera, m_camera.toMatrix());
    m_program->setUniformValue(u_modelToWorld, m_transform.toMatrix()); // yeah
    if (int nCubes = this->figures.first.size()) {
        glDrawArrays(GL_TRIANGLES, 0, 36 * nCubes);
    }
    cubeVAO.release();



    m_program->release();
}

static void qNormalizeAngle(int &angle)
{
    while (angle < 0)
        angle += 360 * 16;
    while (angle > 360)
        angle -= 360 * 16;
}

// ...

void Scene::update()
{
  // Update input
  Input::update();

  static const float transSpeed = 0.5f;
  static const float rotSpeed   = 0.5f;

  // Camera Transformation
  if (Input::buttonPressed(Qt::RightButton))
  {
      // Handle rotations
      m_camera.rotate(-rotSpeed * Input::mouseDelta().x(), Camera3D::LocalUp);
      m_camera.rotate(-rotSpeed * Input::mouseDelta().y(), m_camera.right());
  }
    // Handle translations
  QVector3D translation;
  if (Input::keyPressed(Qt::Key_W))
  {
      translation += m_camera.forward();
  }
  if (Input::keyPressed(Qt::Key_S))
  {
      translation -= m_camera.forward();
  }
  if (Input::keyPressed(Qt::Key_A))
  {
      translation -= m_camera.right();
  }
  if (Input::keyPressed(Qt::Key_D))
  {
      translation += m_camera.right();
  }
  if (Input::keyPressed(Qt::Key_Q))
  {
      translation -= m_camera.up();
  }
  if (Input::keyPressed(Qt::Key_E))
  {
      translation += m_camera.up();
  }
  m_camera.translate(transSpeed * translation);

  if (Input::buttonPressed(Qt::LeftButton)) {
        glClear(GL_COLOR_BUFFER_BIT);
        m_program->bind();
        QOpenGLBuffer buffer;
        buffer.create();
        buffer.setUsagePattern(QOpenGLBuffer::DynamicDraw);
        buffer.bind();
        std::vector<std::vector<Vertex>> fake(this->figures.first);
        for (int j = 0; j < fake.size(); j++) {
            auto cube = fake[j];
            for (int i = 0; i < cube.size(); i+=6) {
                QVector3D color(
                            (i & 0x000000FF) >>  0 >> j,
                            (i & 0x0000FF00) >>  8 >> j,
                            (i & 0x00FF0000) >> 16 >> j
                );
                cube[i].setColor(color);
                cube[i+1].setColor(color);
                cube[i+2].setColor(color);
                cube[i+3].setColor(color);
                cube[i+4].setColor(color);
                cube[i+5].setColor(color);
            }
        }
        buffer.allocate(864 * fake.size());
        for (int i = 0 ; i < fake.size(); i++) {
            auto ptr = buffer.mapRange(864 * i, 864, QOpenGLBuffer::RangeInvalidate | QOpenGLBuffer::RangeWrite);
            memcpy(ptr, fake[i].data(), 864);
            buffer.unmap();
        }
        m_program->enableAttributeArray(0);
        m_program->enableAttributeArray(1);
        m_program->setAttributeBuffer(0, GL_FLOAT, 0, 3, 24);
        m_program->setAttributeBuffer(1, GL_FLOAT, 12, 3, 24);
        glDrawArrays(GL_TRIANGLES, 0, 36 * fake.size());
        buffer.release();
        m_program->release();
  }

  // Update instance information
  //m_transform.rotate(1.0f, QVector3D(0.4f, 0.3f, 0.3f));

  // Schedule a redraw
  QOpenGLWidget::update();
}

void Scene::reloadScene() {
    this->reloadSetup();
    this->update();
}

void Scene::reloadSetup() {
    m_program->bind();
    cubeVAO.bind();
    cubesVBO.bind();
    cubesVBO.allocate(864 * this->figures.first.size());
    for (int i = 0 ; i < this->figures.first.size(); i++) {
        auto ptr = cubesVBO.mapRange(864 * i, 864, QOpenGLBuffer::RangeInvalidate | QOpenGLBuffer::RangeWrite);
        memcpy(ptr, this->figures.first[i].data(), 864);
        cubesVBO.unmap();
    }
    cubesVBO.release();
    cubeVAO.release();
    m_program->release();
}

std::vector<std::vector<Vertex>> Scene::getCoords() {
    std::vector<std::vector<Vertex>> coords(3);
    for (int j = -51; j < 52; j+=2) {
            coords[0].push_back(Vertex(
                            QVector3D(0.0f, float(j), 50.0f),
                            QVector3D(1.0f, 0.0f, 0.0f))
            );
            coords[0].push_back(Vertex(
                            QVector3D(0.0f, float(j), -50.0f),
                            QVector3D(1.0f, 0.0f, 0.0f))
            );

            coords[0].push_back(Vertex(
                            QVector3D(0.0f, 50.0f, float(j)),
                            QVector3D(1.0f, 0.0f, 0.0f))
            );
            coords[0].push_back(Vertex(
                            QVector3D(0.0f, -50.0f, float(j)),
                            QVector3D(1.0f, 0.0f, 0.0f))
            );

            coords[1].push_back(Vertex(
                            QVector3D(float(j), 0.0f, 50.0f),
                            QVector3D(0.0f, 1.0f, 0.0f))
            );
            coords[1].push_back(Vertex(
                            QVector3D(float(j), 0.0f, -50.0f),
                            QVector3D(0.0f, 1.0f, 0.0f))
            );

            coords[1].push_back(Vertex(
                            QVector3D(0.0f, 50.0f, float(j)),
                            QVector3D(0.0f, 1.0f, 0.0f))
            );
            coords[1].push_back(Vertex(
                            QVector3D(0.0f, -50.0f, float(j)),
                            QVector3D(0.0f, 1.0f, 0.0f))
            );

            coords[2].push_back(Vertex(
                            QVector3D(float(j), 50.0f, 0.0f),
                            QVector3D(0.0f, 0.0f, 1.0f))
            );
            coords[2].push_back(Vertex(
                            QVector3D(float(j), -50.0f, 0.0f),
                            QVector3D(0.0f, 0.0f, 1.0f))
            );

            coords[2].push_back(Vertex(
                            QVector3D(50.0f, float(j), 0.0f),
                            QVector3D(0.0f, 0.0f, 1.0f))
            );
            coords[2].push_back(Vertex(
                            QVector3D(-50.0f, float(j), 0.0f),
                            QVector3D(0.0f, 0.0f, 1.0f))
            );
    }
    return coords;
}

std::vector<Vertex> Scene::getAxes() {
    std::vector<Vertex> coords;
    coords.push_back(Vertex(
                    QVector3D(50.0f, 0.0f, 0.0f),
                    QVector3D(1.0f, 1.0f, 1.0f))
    );
    coords.push_back(Vertex(
                    QVector3D(-50.0f, 0.0f, 0.0f),
                    QVector3D(1.0f, 1.0f, 1.0f))
    );
    coords.push_back(Vertex(
                    QVector3D(0.0f, 50.0f, 0.0f),
                    QVector3D(1.0f, 1.0f, 1.0f))
    );
    coords.push_back(Vertex(
                    QVector3D(0.0f, -50.0f, 0.0f),
                    QVector3D(1.0f, 1.0f, 1.0f))
    );
    coords.push_back(Vertex(
                    QVector3D(0.0f, 0.0f, 50.0f),
                    QVector3D(1.0f, 1.0f, 1.0f))
    );
    coords.push_back(Vertex(
                    QVector3D(0.0f, 0.0f, -50.0f),
                    QVector3D(1.0f, 1.0f, 1.0f))
    );
    return coords;
}

void Scene::keyPressEvent(QKeyEvent *event)
{
  if (event->isAutoRepeat())
  {
    event->ignore();
  }
  else
  {
    Input::registerKeyPress(event->key());
  }
}

void Scene::keyReleaseEvent(QKeyEvent *event)
{
  if (event->isAutoRepeat())
  {
    event->ignore();
  }
  else
  {
    Input::registerKeyRelease(event->key());
  }
}

void Scene::mousePressEvent(QMouseEvent *event)
{
  Input::registerMousePress(event->button());

}

void Scene::mouseReleaseEvent(QMouseEvent *event)
{
  Input::registerMouseRelease(event->button());
}

// ...
