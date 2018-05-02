#include "dbaccessor.h"

DBAccessor::DBAccessor() {
  QSqlDatabase::addDatabase("QPSQL");
  this->db = QSqlDatabase::database();
  this->db.setHostName("localhost");
  this->db.setDatabaseName("postgres");
  this->db.setUserName("postgres");
  this->db.setPort(5432);
  this->saveCubeVertex = new QSqlQuery(this->db);
  this->savePrismVertex = new QSqlQuery(this->db);
}

void DBAccessor::persist(
    QString tableName,
    std::pair<std::vector<Cube>, std::vector<Prism>> figures) {
  QString cubeTableName = tableName + "_cubes";
  QString prismTableName = tableName + "_prisms";
  this->db.open();
  this->db.exec(QString("DROP TABLE IF EXISTS " + cubeTableName + ";"));
  this->db.exec(QString("DROP TABLE IF EXISTS " + prismTableName + ";"));
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
      QString("INSERT INTO " + cubeTableName + " VALUES (?, ?, ?)"));
  this->savePrismVertex->prepare(
      QString("INSERT INTO " + prismTableName + " VALUES (?, ?, ?)"));

  auto cubes = figures.first;
  auto prisms = figures.second;

  for (int i = 0; i < cubes.size(); i++) {
    for (int j = 0; j < 24; j++) {
      this->saveCubeVertex->bindValue(0, cubes[i].getDots()[j].position().x());
      this->saveCubeVertex->bindValue(1, cubes[i].getDots()[j].position().y());
      this->saveCubeVertex->bindValue(2, cubes[i].getDots()[j].position().z());
      this->saveCubeVertex->exec();
    }
    this->saveCubeVertex->bindValue(0, cubes[i].getColor().x());
    this->saveCubeVertex->bindValue(1, cubes[i].getColor().y());
    this->saveCubeVertex->bindValue(2, cubes[i].getColor().z());
    this->saveCubeVertex->exec();
  }
  for (int i = 0; i < prisms.size(); i++) {
    for (int j = 0; j < 36; j++) {
      this->savePrismVertex->bindValue(0,
                                       prisms[i].getDots()[j].position().x());
      this->savePrismVertex->bindValue(1,
                                       prisms[i].getDots()[j].position().y());
      this->savePrismVertex->bindValue(2,
                                       prisms[i].getDots()[j].position().z());
      this->savePrismVertex->exec();
    }
    this->savePrismVertex->bindValue(0, prisms[i].getColor().x());
    this->savePrismVertex->bindValue(1, prisms[i].getColor().y());
    this->savePrismVertex->bindValue(2, prisms[i].getColor().z());
    this->savePrismVertex->exec();
  }
  this->db.close();
}

std::pair<std::vector<Cube>, std::vector<Prism>>
DBAccessor::load(QString tableName) {
  QString cubeTableName = tableName + "_cubes";
  QString prismTableName = tableName + "_prisms";
  bool ok = this->db.open();
  QSqlQuery loadCubesQuery(this->db);
  loadCubesQuery.setForwardOnly(true);

  loadCubesQuery.exec(QString("SELECT x, y, z FROM " + cubeTableName + ";"));

  std::vector<Cube> cubes;
  std::vector<Prism> prisms;

  int nCubeVertices = 0;
  Cube aCube;
  aCube.getDots().resize(24);

  while (loadCubesQuery.next()) {
    QVector3D vertexVector(loadCubesQuery.value(0).toFloat(),
                           loadCubesQuery.value(1).toFloat(),
                           loadCubesQuery.value(2).toFloat());
    if (nCubeVertices == 24) {
      aCube.setColor(vertexVector);
      cubes.push_back(aCube);
      nCubeVertices = 0;
      continue;
    }
    aCube.getDots()[nCubeVertices++] = Vertex(vertexVector);
  }

  QSqlQuery loadPrimsQuery(this->db);
  loadPrimsQuery.setForwardOnly(true);

  loadPrimsQuery.exec(QString("SELECT x, y, z FROM " + prismTableName + ";"));

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
  this->db.close();
  return {cubes, prisms};
}
