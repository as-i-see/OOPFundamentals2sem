#include "loader.h"
#include "ui_loader.h"
#include <QSqlRecord>
#include <QString>

Loader::Loader(QWidget *parent) : QMainWindow(parent), ui(new Ui::Loader) {
  ui->setupUi(this);
  connect(ui->pushButton, SIGNAL(clicked(bool)), this, SLOT(load()));
  this->db = QSqlDatabase::database();
  this->db.setHostName("localhost");
  this->db.setDatabaseName("postgres");
  this->db.setUserName("postgres");
  this->db.setPort(5432);
}

Loader::~Loader() { delete ui; }

void Loader::load() {
  QString tableName = ui->lineEdit->text();
  this->cubeTableName = tableName + "_cubes";
  this->prismTableName = tableName + "_prisms";
  bool ok = this->db.open();
  QSqlQuery loadCubesQuery(this->db);
  loadCubesQuery.setForwardOnly(true);

  loadCubesQuery.exec(
      QString("SELECT x, y, z FROM " + this->cubeTableName + ";"));

  std::vector<Cube> cubes;
  std::vector<Prism> prisms;

  int nCubeVertices = 0;
  Cube aCube;
  aCube.getDots().resize(36);

  while (loadCubesQuery.next()) {
    QVector3D vertexVector(loadCubesQuery.value(0).toFloat(),
                           loadCubesQuery.value(1).toFloat(),
                           loadCubesQuery.value(2).toFloat());
    if (nCubeVertices == 36) {
      aCube.setColor(vertexVector);
      cubes.push_back(aCube);
      nCubeVertices = 0;
      continue;
    }
    aCube.getDots()[nCubeVertices++] = Vertex(vertexVector);
  }

  QSqlQuery loadPrimsQuery(this->db);
  loadPrimsQuery.setForwardOnly(true);

  loadPrimsQuery.exec(
      QString("SELECT x, y, z FROM " + this->prismTableName + ";"));

  int nPrismVertices = 0;
  Prism aPrism;
  aPrism.getDots().resize(36);

  while (loadPrimsQuery.next()) {
    QVector3D vertexVector(loadPrimsQuery.value(0).toFloat(),
                           loadPrimsQuery.value(1).toFloat(),
                           loadPrimsQuery.value(2).toFloat());
    if (nPrismVertices == 36) {
      aPrism.setColor(vertexVector);
      prisms.push_back(aPrism);
      nPrismVertices = 0;
      continue;
    }
    aPrism.getDots()[nPrismVertices++] = Vertex(vertexVector);
  }
  emit sendData({cubes, prisms});
  this->db.close();
  this->close();
}
