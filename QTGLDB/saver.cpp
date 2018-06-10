#include "saver.h"
#include "ui_saver.h"
#include <iostream>

Saver::Saver(QWidget *parent) : QMainWindow(parent), ui(new Ui::Saver) {
  ui->setupUi(this);
  connect(ui->pushButton, SIGNAL(clicked(bool)), this, SLOT(persist()));
}

Saver::~Saver() { delete ui; }

void Saver::persist() {
  QString tableName = ui->lineEdit->text();

  std::pair<std::vector<Cylinder>, std::vector<Prism>> config(
      std::move(std::vector<Cylinder>()), std::move(std::vector<Prism>()));
  emit dataUpdate(config);
  auto cubes = config.first;
  auto prisms = config.second;
  applyLiveTransformations(cubes, prisms);

  this->dbAccessor->persist(tableName, {cubes, prisms});

  this->close();
  ui->lineEdit->setText("");
}

void Saver::applyLiveTransformations(std::vector<Cylinder> &cubes,
                                     std::vector<Prism> &prisms) {
  for (int i = 0; i < cubes.size(); i++) {
    for (int j = 0; j < 24; j++) {
      cubes[i].getDots()[j].setPosition(cubes[i].transform.toMatrix() *
                                        cubes[i].getDots()[j].position());
    }
  }
  for (int i = 0; i < prisms.size(); i++) {
    for (int j = 0; j < 36; j++) {
      prisms[i].getDots()[j].setPosition(prisms[i].transform.toMatrix() *
                                         prisms[i].getDots()[j].position());
    }
  }
}

void Saver::setDBAccessor(DBAccessor *accessor) { this->dbAccessor = accessor; }
