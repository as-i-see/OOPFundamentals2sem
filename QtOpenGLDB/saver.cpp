#include "saver.h"
#include "ui_saver.h"
#include <iostream>

Saver::Saver(QMainWindow *parent) :
    ui(new Ui::Saver)
{
    ui->setupUi(this);
    connect(ui->pushButton, SIGNAL(clicked(bool)), this, SLOT(persist()));
    this->db = QSqlDatabase::addDatabase("QPSQL");
    this->db.setHostName("localhost");
    this->db.setDatabaseName("postgres");
    this->db.setUserName("postgres");
    this->db.setPort(5432);
    this->saveCubeVertex = new QSqlQuery(this->db);
    this->savePrismVertex = new QSqlQuery(this->db);

}

Saver::~Saver()
{
    delete ui;
}

bool Saver::persist() {
    QString tableName = ui->lineEdit->text();
    this->cubeTableName = tableName + "_cubes";
    this->prismTableName = tableName + "_prisms";
    bool ok = this->db.open();
    this->db.exec(QString(
       "CREATE TABLE " + cubeTableName + " ("
                                                "  xPos   NUMERIC(6,4), "
                                                "  yPos   NUMERIC(6,4), "
                                                "  zPos   NUMERIC(6,4), "
                                                "  xColor NUMERIC(6,4), "
                                                "  yColor NUMERIC(6,4), "
                                                "  zColor NUMERIC(6,4)  "
                                                 ")"
    ));
    this->db.exec(QString(
       "CREATE TABLE " + prismTableName + " ("
                                                "  xPos   NUMERIC(6,4), "
                                                "  yPos   NUMERIC(6,4), "
                                                "  zPos   NUMERIC(6,4), "
                                                "  xColor NUMERIC(6,4), "
                                                "  yColor NUMERIC(6,4), "
                                                "  zColor NUMERIC(6,4)  "
                                                 ")"
    ));
    this->saveCubeVertex->prepare(QString(
                          "INSERT INTO " + this->cubeTableName + " VALUES (?, ?, ?, ?, ?, ?)"
    ));
    this->savePrismVertex->prepare(QString(
                          "INSERT INTO " + this->prismTableName + " VALUES (?, ?, ?, ?, ?, ?)"
    ));
    for (auto cube: this->data) {
        for (auto vertex : cube) {
            this->saveCubeVertex->bindValue(0, vertex.position().x());
            this->saveCubeVertex->bindValue(1, vertex.position().y());
            this->saveCubeVertex->bindValue(2, vertex.position().z());
            this->saveCubeVertex->bindValue(3, vertex.color().x());
            this->saveCubeVertex->bindValue(4, vertex.color().y());
            this->saveCubeVertex->bindValue(5, vertex.color().z());
            if (!this->saveCubeVertex->exec()) {
                QSqlError err = this->saveCubeVertex->lastError();
                std::cout << err.databaseText().toStdString();
            }
        }
    }
    this->db.close();
    this->close();
    return ok;
}

void Saver::setData(std::vector<std::vector<Vertex>> data) {
    this->data = data;
}
