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
#include "camera3d.h"

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
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
protected slots:
    void update();
private:
    int xRot;
    int yRot;
    int zRot;

    QPoint lastPos;

    QOpenGLShaderProgram *m_program;
    QOpenGLVertexArrayObject cubeVAO, coordsVAO;
    QOpenGLBuffer cubesVBO, coordsVBO;

    // Shader Information
    int u_modelToWorld;
    int u_worldToCamera;
    int u_cameraToView;
    QMatrix4x4 m_projection;
    Transform3D m_transform;
    Camera3D m_camera;

    void reloadSetup();

    std::vector<std::vector<Vertex>> getCoords();
    std::vector<Vertex> getAxes();
};

#endif // SCENE_H
