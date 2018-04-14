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

    QOpenGLBuffer m_vertex;
    QOpenGLVertexArrayObject m_object;
    std::vector<QOpenGLBuffer> cubeBuffers;
    std::vector<QOpenGLVertexArrayObject> cubeObjects;
    QOpenGLShaderProgram *m_program;

    // Shader Information
    int u_modelToWorld;
    int u_worldToView;
    QMatrix4x4 m_projection;
    Transform3D m_transform;
    void reloadSetup();
    void clearVBOsAndVAOs();

};

#endif // SCENE_H
