#ifndef CUBECREATION_H
#define CUBECREATION_H

#include <QMainWindow>
#include <QLabel>
#include <QColor>
#include <vector>
#include <string>
#include <QPalette>
#include <QLineEdit>
#include "vertex.h"
#include <QDebug>
#include <QRegExp>
#include <QValidator>

namespace Ui {
class CubeCreation;
}

class CubeCreation : public QMainWindow
{
    Q_OBJECT

public:
    explicit CubeCreation(QWidget *parent = 0);
    ~CubeCreation();
signals:
    void newCubeReady(std::vector<Vertex>);
private slots:
    void on_pushButton_clicked(bool checked);

private:
    Ui::CubeCreation *ui;
    QLabel *dotLetter;
    int currentDot;
    QColor colors[4] = {Qt::red, Qt::yellow, Qt::green, Qt::blue};
    std::vector<std::string> dots = {"A", "D", "B", "A1"};
    QPalette *currentPalette;
    QLineEdit *x, *y, *z;
    std::vector<Vertex> input;
    QRegExp *floatRegExp;
    bool isCube(const std::vector<Vertex>&);
    std::vector<Vertex> makeCubeVertices(std::vector<Vertex>);
};

#endif // CUBECREATION_H
