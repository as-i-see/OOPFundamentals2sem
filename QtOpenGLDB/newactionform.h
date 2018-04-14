#ifndef NEWACTIONFORM_H
#define NEWACTIONFORM_H

#include <QWidget>
#include <QLabel>
#include <QDebug>
#include <QPushButton>
#include "cubecreation.h"

namespace Ui {
class NewActionForm;
}

class NewActionForm : public QWidget
{
    Q_OBJECT

public:
    explicit NewActionForm(QMainWindow *parent = 0);
    ~NewActionForm();
signals:
    void creationCompleted(std::pair<std::vector<std::vector<Vertex>>, int>);
public slots:
    void creationCompleted();
    void newCubeReady(std::vector<Vertex>);
private:
    QMainWindow *parent;
    Ui::NewActionForm *ui;
    QLabel *cubesLabel, *prismsLabel;
    QPushButton *cubeButton, *submitButton;
    CubeCreation *cubeCreation;
    std::vector<std::vector<Vertex>> cubes;

};

#endif // NEWACTIONFORM_H
