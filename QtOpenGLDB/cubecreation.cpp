#include "cubecreation.h"
#include "ui_cubecreation.h"
#include <cstring>
#include <QVector3D>
#include <QMessageBox>

CubeCreation::CubeCreation(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CubeCreation)
{
    ui->setupUi(this);
    this->dotLetter = ui->label_6;
    this->currentDot = 0;
    this->currentPalette = new QPalette();
    this->x = ui->lineEdit;
    this->y = ui->lineEdit_2;
    this->z = ui->lineEdit_3;
    this->floatRegExp = new QRegExp("[-+]?([0-9]*\.[0-9]+|[0-9]+)");
}

CubeCreation::~CubeCreation()
{
    delete ui;
}

void CubeCreation::on_pushButton_clicked(bool checked)
{
    if (!this->floatRegExp->exactMatch(this->x->text()) ||
    (!this->floatRegExp->exactMatch(this->y->text())) ||
    (!this->floatRegExp->exactMatch(this->z->text()))) {
        QMessageBox alertErrorBox;
        alertErrorBox.setText("You must enter either float or integer values!");
        alertErrorBox.setIcon(QMessageBox::Critical);
        alertErrorBox.setWindowTitle("ERROR");
        alertErrorBox.exec();
        this->currentDot--;
        return;
    }
    float x = this->x->text().toFloat();
    float y = this->y->text().toFloat();
    float z = this->z->text().toFloat();
    this->x->setText("0");
    this->y->setText("0");
    this->z->setText("0");
    Vertex *vertex = new Vertex(QVector3D(x, y, z));
    this->input.push_back(*vertex);
    if (currentDot == 3) {
        if (!isCube(this->input)) {
            QMessageBox alertErrorBox;
            alertErrorBox.setText("The input is not a cube");
            alertErrorBox.setIcon(QMessageBox::Critical);
            alertErrorBox.setWindowTitle("ERROR");
            alertErrorBox.exec();
        }
        else {
            auto vertices = makeCubeVertices(this->input);
            emit newCubeReady(vertices);
        }
        currentDot = -1;
        this->x->setText("0");
        this->y->setText("0");
        this->z->setText("0");
        this->input.clear();
        this->close();
    }
    this->currentPalette->setColor(QPalette::WindowText, this->colors[++this->currentDot]);
    this->dotLetter->setPalette(*currentPalette);
    this->dotLetter->setText(this->dots[currentDot].c_str());
}

bool CubeCreation::isCube(const std::vector<Vertex>& input) {
    float sideLen = input[0].position().distanceToPoint(input[1].position());
    float diagonalLen = pow(2.0, 0.5) * sideLen;
    bool isCube = true;
    isCube = (input[0].position().distanceToPoint(input[2].position()) == sideLen);
    isCube = (input[0].position().distanceToPoint(input[3].position()) == sideLen);
    isCube = (input[1].position().distanceToPoint(input[2].position()) == diagonalLen);
    isCube = (input[1].position().distanceToPoint(input[3].position()) == diagonalLen);
    isCube = (input[2].position().distanceToPoint(input[3].position()) == diagonalLen);
    return isCube;
}

std::vector<Vertex> CubeCreation::makeCubeVertices(std::vector<Vertex> input) {
    QVector3D whiteColor(1.0f, 1.0f, 1.0f);
    Vertex VERTEX_FBL(input[0].position(), whiteColor);
    Vertex VERTEX_FBR(input[1].position(), whiteColor);
    Vertex VERTEX_FTL(input[3].position(), whiteColor);
    Vertex VERTEX_BBL(input[2].position(), whiteColor);
    QVector3D upVector = VERTEX_FTL.position() - VERTEX_FBL.position();
    QVector3D frontwardVector = VERTEX_BBL.position() - VERTEX_FBL.position();
    Vertex VERTEX_FTR(VERTEX_FBR.position() + upVector, whiteColor);
    Vertex VERTEX_BTL(VERTEX_FTL.position() + frontwardVector, whiteColor);
    Vertex VERTEX_BTR(VERTEX_FTR.position() + frontwardVector, whiteColor);
    Vertex VERTEX_BBR(VERTEX_FBR.position() + frontwardVector, whiteColor);
    std::vector<Vertex> vertices = {
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
    return vertices;
}
