#include "cylindercreation.h"
#include "ui_cylindercreation.h"
#include <QMessageBox>
#include <QVector3D>
#include <cstring>

CylinderCreation::CylinderCreation(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::CylinderCreation) {
  ui->setupUi(this);
  this->dotLetter = ui->label_6;
  this->nDotsRead = 0;
  this->currentPalette = new QPalette();
  this->x = ui->lineEdit;
  this->y = ui->lineEdit_2;
  this->z = ui->lineEdit_3;
  this->floatRegExp = new QRegExp("[-+]?([0-9]*\.[0-9]+|[0-9]+)");
}

CylinderCreation::~CylinderCreation() { delete ui; }

void CylinderCreation::on_pushButton_clicked(bool checked) {
  if (!this->floatRegExp->exactMatch(this->x->text()) ||
      (!this->floatRegExp->exactMatch(this->y->text())) ||
      (!this->floatRegExp->exactMatch(this->z->text()))) {
    QMessageBox alertErrorBox;
    alertErrorBox.setText("You must enter either float or integer values!");
    alertErrorBox.setIcon(QMessageBox::Critical);
    alertErrorBox.setWindowTitle("ERROR");
    alertErrorBox.exec();
    this->nDotsRead--;
    return;
  }
  float x = this->x->text().toFloat();
  float y = this->y->text().toFloat();
  float z = this->z->text().toFloat();
  this->x->setText("0");
  this->y->setText("0");
  this->z->setText("0");
  Vertex vertex(QVector3D(x, y, z));
  this->cylinder.getDots().push_back(vertex);
  if (nDotsRead == 3) {
    if (!this->cylinder.isValid()) {
      QMessageBox alertErrorBox;
      alertErrorBox.setText("The input is not a cube");
      alertErrorBox.setIcon(QMessageBox::Critical);
      alertErrorBox.setWindowTitle("ERROR");
      alertErrorBox.exec();
    } else {
      this->cylinder.reconstruct();
      emit newCylinderReady(this->cylinder);
    }
    nDotsRead = -1;
    this->x->setText("0");
    this->y->setText("0");
    this->z->setText("0");
    this->cylinder.getDots().clear();
    this->close();
  }
  this->currentPalette->setColor(QPalette::WindowText,
                                 this->colors[++this->nDotsRead]);
  this->dotLetter->setPalette(*currentPalette);
  this->dotLetter->setText(this->dots[nDotsRead].c_str());
}
