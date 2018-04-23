#include "saver.h"
#include "ui_saver.h"
#include <iostream>

Saver::Saver(QMainWindow *parent) : ui(new Ui::Saver) {
  ui->setupUi(this);
  connect(ui->pushButton, SIGNAL(clicked(bool)), this, SLOT(persist()));
  this->db = QSqlDatabase::database();
  this->db.setHostName("localhost");
  this->db.setDatabaseName("postgres");
  this->db.setUserName("postgres");
  this->db.setPort(5432);
  this->saveCubeVertex = new QSqlQuery(this->db);
  this->savePrismVertex = new QSqlQuery(this->db);
}

Saver::~Saver() { delete ui; }

bool Saver::persist() {
  QString tableName = ui->lineEdit->text();
  this->cubeTableName = tableName + "_cubes";
  this->prismTableName = tableName + "_prisms";
  bool ok = this->db.open();
  this->db.exec(QString("CREATE TABLE " + cubeTableName +
                        " ("
                        "  x   NUMERIC(6,4), "
                        "  y   NUMERIC(6,4), "
                        "  z   NUMERIC(6,4)  "
                        ")"));
  this->db.exec(QString("CREATE TABLE " + prismTableName +
                        " ("
                        "  x   NUMERIC(6,4), "
                        "  y   NUMERIC(6,4), "
                        "  z   NUMERIC(6,4)  "
                        ")"));
  this->saveCubeVertex->prepare(
      QString("INSERT INTO " + this->cubeTableName + " VALUES (?, ?, ?)"));
  this->savePrismVertex->prepare(
      QString("INSERT INTO " + this->prismTableName + " VALUES (?, ?, ?)"));
  std::pair<std::vector<Cube>, std::vector<Prism>> config(
      std::move(std::vector<Cube>()), std::move(std::vector<Prism>()));
  emit dataUpdate(config);
  this->cubes = config.first;
  this->prisms = config.second;
  applyLiveTransformations();
  for (int i = 0; i < this->cubes.size(); i++) {
    for (int j = 0; j < 36; j++) {
      this->saveCubeVertex->bindValue(
          0, this->cubes[i].getDots()[j].position().x());
      this->saveCubeVertex->bindValue(
          1, this->cubes[i].getDots()[j].position().y());
      this->saveCubeVertex->bindValue(
          2, this->cubes[i].getDots()[j].position().z());
      if (!this->saveCubeVertex->exec()) {
        QSqlError err = this->saveCubeVertex->lastError();
        std::cout << err.databaseText().toStdString();
      }
    }
    this->saveCubeVertex->bindValue(0, this->cubes[i].getColor().x());
    this->saveCubeVertex->bindValue(1, this->cubes[i].getColor().y());
    this->saveCubeVertex->bindValue(2, this->cubes[i].getColor().z());
    if (!this->saveCubeVertex->exec()) {
      QSqlError err = this->saveCubeVertex->lastError();
      std::cout << err.databaseText().toStdString();
    }
  }
  for (int i = 0; i < this->prisms.size(); i++) {
    for (int j = 0; j < 36; j++) {
      this->savePrismVertex->bindValue(
          0, this->prisms[i].getDots()[j].position().x());
      this->savePrismVertex->bindValue(
          1, this->prisms[i].getDots()[j].position().y());
      this->savePrismVertex->bindValue(
          2, this->prisms[i].getDots()[j].position().z());
      if (!this->savePrismVertex->exec()) {
        QSqlError err = this->savePrismVertex->lastError();
        std::cout << err.databaseText().toStdString();
      }
    }
    this->savePrismVertex->bindValue(0, this->prisms[i].getColor().x());
    this->savePrismVertex->bindValue(1, this->prisms[i].getColor().y());
    this->savePrismVertex->bindValue(2, this->prisms[i].getColor().z());
    if (!this->savePrismVertex->exec()) {
      QSqlError err = this->savePrismVertex->lastError();
      std::cout << err.databaseText().toStdString();
    }
  }
  this->db.close();
  this->close();
  ui->lineEdit->setText("");
  return ok;
}

void Saver::applyLiveTransformations() {
  for (int i = 0; i < this->cubes.size(); i++) {
    for (int j = 0; j < 36; j++) {
      this->cubes[i].getDots()[j].setPosition(
          this->cubes[i].transform.toMatrix() *
          this->cubes[i].getDots()[j].position());
    }
  }
  for (int i = 0; i < this->prisms.size(); i++) {
    for (int j = 0; j < 36; j++) {
      this->prisms[i].getDots()[j].setPosition(
          this->prisms[i].transform.toMatrix() *
          this->prisms[i].getDots()[j].position());
    }
  }
}
