#ifndef SCENE_H
#define SCENE_H
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QMouseEvent>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QMatrix4x4>
#include "transform3d.h"
#include <vector>
#include "vertex.h"

class QOpenGLShaderProgram;

class Scene : public QOpenGLWidget//, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    Scene(QWidget* parent);
    std::pair<std::vector<std::vector<Vertex>>, int> figures;
public slots:
    void reloadScene();
protected:
    void initializeGL();
    void resizeGL(int, int);
    void paintGL();
    //void teardownGL();
protected slots:
    void update();
private:
    int xRot;
    int yRot;
    int zRot;

    QPoint lastPos;

    QOpenGLShaderProgram *m_program;
    QOpenGLVertexArrayObject cubeVAO;
    QOpenGLBuffer cubesVBO;

    // Shader Information
    int u_modelToWorld;
    int u_worldToView;
    QMatrix4x4 m_projection;
    Transform3D m_transform;
    void reloadSetup();
};

#endif // SCENE_H
