#include "scene.h"
#include <QString>
#include <QOpenGLShaderProgram>
#include "vertex.h"

// Front Verticies
#define VERTEX_FTR Vertex( QVector3D( 0.5f,  0.5f,  0.5f), QVector3D( 1.0f, 0.0f, 0.0f ) )
#define VERTEX_FTL Vertex( QVector3D(-0.5f,  0.5f,  0.5f), QVector3D( 0.0f, 1.0f, 0.0f ) )
#define VERTEX_FBL Vertex( QVector3D(-0.5f, -0.5f,  0.5f), QVector3D( 0.0f, 0.0f, 1.0f ) )
#define VERTEX_FBR Vertex( QVector3D( 0.5f, -0.5f,  0.5f), QVector3D( 0.0f, 0.0f, 0.0f ) )

// Back Verticies
#define VERTEX_BTR Vertex( QVector3D( 0.5f,  0.5f, -0.5f), QVector3D( 1.0f, 1.0f, 0.0f ) )
#define VERTEX_BTL Vertex( QVector3D(-0.5f,  0.5f, -0.5f), QVector3D( 0.0f, 1.0f, 1.0f ) )
#define VERTEX_BBL Vertex( QVector3D(-0.5f, -0.5f, -0.5f), QVector3D( 1.0f, 0.0f, 1.0f ) )
#define VERTEX_BBR Vertex( QVector3D( 0.5f, -0.5f, -0.5f), QVector3D( 1.0f, 1.0f, 1.0f ) )

// Create a colored cube
static Vertex sg_vertexes[] = {
  // Face 1 (Front)
    VERTEX_FTR, VERTEX_FTL, VERTEX_FBL,
    VERTEX_FBL, VERTEX_FBR, VERTEX_FTR,
  // Face 2 (Back)
    VERTEX_BBR, VERTEX_BTL, VERTEX_BTR,
    VERTEX_BTL, VERTEX_BBR, VERTEX_BBL,
  // Face 3 (Top)
    VERTEX_FTR, VERTEX_BTR, VERTEX_BTL,
    VERTEX_BTL, VERTEX_FTL, VERTEX_FTR,
  // Face 4 (Bottom)
    VERTEX_FBR, VERTEX_FBL, VERTEX_BBL,
    VERTEX_BBL, VERTEX_BBR, VERTEX_FBR,
  // Face 5 (Left)
    VERTEX_FBL, VERTEX_FTL, VERTEX_BTL,
    VERTEX_FBL, VERTEX_BTL, VERTEX_BBL,
  // Face 6 (Right)
    VERTEX_FTR, VERTEX_FBR, VERTEX_BBR,
    VERTEX_BBR, VERTEX_BTR, VERTEX_FTR
};


Scene::Scene(QWidget* parent) : QOpenGLWidget(parent)
{
    m_transform.translate(0.0f, 0.0f, -5.0f);
}

void Scene::initializeGL() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    connect(this, SIGNAL(frameSwapped()), this, SLOT(update()));
    glEnable(GL_CULL_FACE);

    m_program = new QOpenGLShaderProgram();
    m_program->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/simple.vert");
    m_program->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/simple.frag");
    m_program->link();
    m_program->bind();

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
        cubesVBO.unmap();
    }
    cubesVBO.release();
    cubeVAO.release();
    m_program->release();
}
