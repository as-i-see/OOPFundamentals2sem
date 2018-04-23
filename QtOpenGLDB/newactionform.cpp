#include "newactionform.h"
#include "ui_newactionform.h"

NewActionForm::NewActionForm(QMainWindow *parent)
    : parent(parent), ui(new Ui::NewActionForm) {
  ui->setupUi(this);
  this->cubesLabel = ui->label;
  this->prismsLabel = ui->label_2;
  this->cubeCreation = new CubeCreation(this);
  this->prismCreation = new PrismCreation(this);
  connect(ui->pushButton, SIGNAL(clicked(bool)), this->cubeCreation,
          SLOT(show()));
  connect(ui->pushButton_2, SIGNAL(clicked(bool)), this->prismCreation,
          SLOT(show()));
  connect(this->cubeCreation, SIGNAL(newCubeReady(Cube)), this,
          SLOT(newCubeReady(Cube)));
  connect(this->prismCreation, SIGNAL(newPrismReady(Prism)), this,
          SLOT(newPrismReady(Prism)));
  connect(ui->pushButton_3, SIGNAL(clicked(bool)), this,
          SLOT(creationCompleted()));
}

NewActionForm::~NewActionForm() { delete ui; }

void NewActionForm::newCubeReady(Cube cube) {
  this->cubes.push_back(cube);
  QString presentText = this->cubesLabel->text();
  this->cubesLabel->setText(presentText + "Cube #" +
                            QString::number(this->cubes.size()) + "\n");
}

void NewActionForm::newPrismReady(Prism prism) {
  this->prisms.push_back(prism);
  QString presentText = this->prismsLabel->text();
  this->prismsLabel->setText(presentText + "Prism #" +
                             QString::number(this->prisms.size()) + "\n");
}

void NewActionForm::creationCompleted() {
  emit creationCompleted({this->cubes, this->prisms});
  this->cubesLabel->setText("");
  this->prismsLabel->setText("");
  for (int i = 0; i < this->cubes.size(); i++) {
    this->cubes[i].getDots().clear();
  }
  for (int i = 0; i < this->prisms.size(); i++) {
    this->prisms[i].getDots().clear();
  }
  this->cubes.clear();
  this->prisms.clear();
  this->close();
}
