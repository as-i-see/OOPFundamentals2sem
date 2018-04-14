#include "scene.h"
#include <QString>
#include <QOpenGLShaderProgram>
#include "vertex.h"

Scene::Scene(QWidget* parent) : QOpenGLWidget(parent)
{
    m_transform.translate(0.0f, 0.0f, -5.0f);
}

void Scene::initializeGL() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    connect(this, SIGNAL(frameSwapped()), this, SLOT(update()));
    glEnable(GL_CULL_FACE);
    glLineWidth(2.0f);

    m_program = new QOpenGLShaderProgram();
    m_program->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/simple.vert");
    m_program->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/simple.frag");
    m_program->link();
    m_program->bind();

    /////////////////////////////////

    cubeVAO.create();
    cubeVAO.bind();

    u_modelToWorld = m_program->uniformLocation("modelToWorld");
    u_worldToView = m_program->uniformLocation("worldToView");

    cubesVBO.create();
    cubesVBO.setUsagePattern(QOpenGLBuffer::DynamicDraw);
    cubesVBO.bind();

    m_program->enableAttributeArray(0);
    m_program->enableAttributeArray(1);
    m_program->setAttributeBuffer(0, GL_FLOAT, 0, Vertex::PositionTupleSize, Vertex::stride());
    m_program->setAttributeBuffer(1, GL_FLOAT, 3 * sizeof(float), Vertex::ColorTupleSize, Vertex::stride());

    cubesVBO.release();
    cubeVAO.release();

    //////////////////////////////////

    coordsVAO.create();
    coordsVAO.bind();

    u_modelToWorld = m_program->uniformLocation("modelToWorld");
    u_worldToView = m_program->uniformLocation("worldToView");

    coordsVBO.create();
    coordsVBO.setUsagePattern(QOpenGLBuffer::StaticDraw);
    coordsVBO.bind();

    m_program->enableAttributeArray(0);
    m_program->enableAttributeArray(1);
    m_program->setAttributeBuffer(0, GL_FLOAT, 0, Vertex::PositionTupleSize, Vertex::stride());
    m_program->setAttributeBuffer(1, GL_FLOAT, 3 * sizeof(float), Vertex::ColorTupleSize, Vertex::stride());

    coordsVBO.allocate(3 * 2 * 121 * sizeof(Vertex));
    auto coordsVec = getCoords();
    for (int i = 0 ; i < 3; i++) {
        auto ptr = coordsVBO.mapRange(2 * 121 * sizeof(Vertex) * i, 2 * 121 * sizeof(Vertex), QOpenGLBuffer::RangeInvalidate | QOpenGLBuffer::RangeWrite);
        auto arr = coordsVec[i].data();

        //memcpy(ptr, coordsVec[i].data(), 2 * 121 * sizeof(Vertex));
    }
//    coordsVBO.unmap();


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
    m_program->bind();
    cubeVAO.bind();
    m_program->setUniformValue(u_worldToView, m_projection);
    m_program->setUniformValue(u_modelToWorld, m_transform.toMatrix());
    if (int nCubes = this->figures.first.size()) {
        glDrawArrays(GL_TRIANGLES, 0, 36 * nCubes);
    }
    cubeVAO.release();

//    coordsVAO.bind();
//    m_program->setUniformValue(u_worldToView, QMatrix4x4());
//    m_program->setUniformValue(u_modelToWorld, QMatrix4x4());
//    glDrawArrays(GL_LINES, 0, 3 * 2 * 121);
//    coordsVAO.release();

    m_program->release();
}

static void qNormalizeAngle(int &angle)
{
    while (angle < 0)
        angle += 360 * 16;
    while (angle > 360)
        angle -= 360 * 16;
}

void Scene::update()
{
  // Update instance information
  m_transform.rotate(1.0f, QVector3D(0.4f, 0.3f, 0.3f));

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
    }
    cubesVBO.unmap();
    cubesVBO.release();
    cubeVAO.release();
    m_program->release();
}

std::vector<std::vector<Vertex>> Scene::getCoords() {
    std::vector<std::vector<Vertex>> coords(3);
    std::vector<QVector3D> colors = {
        QVector3D(1.0f, 0.0f, 0.0f),
        QVector3D(0.0f, 1.0f, 0.0f),
        QVector3D(0.0f, 0.0f, 1.0f),
    };
    for (int j = -5; j < 6; j++) {
        for (int k = -5; k < 6; k++) {
            coords[0].push_back(Vertex(
                            QVector3D(-1.0f, float(j), float(k)),
                            colors[0])
            );
            coords[0].push_back(Vertex(
                            QVector3D(1.0f, float(j), float(k)),
                            colors[0])
            );
        }
    }
    for (int j = -5; j < 6; j++) {
        for (int k = -5; k < 6; k++) {
            coords[1].push_back(Vertex(
                            QVector3D(float(j), -1.0f, float(k)),
                            colors[1])
            );
            coords[1].push_back(Vertex(
                            QVector3D(float(j), 1.0f, float(k)),
                            colors[1])
            );
        }
    }

    for (int j = -5; j < 6; j++) {
        for (int k = -5; k < 6; k++) {
            coords[2].push_back(Vertex(
                            QVector3D(float(j), float(k), -1.0f),
                            colors[2])
            );
            coords[2].push_back(Vertex(
                            QVector3D(float(j), float(k), 1.0f),
                            colors[2])
            );
        }
    }
    return coords;
}
