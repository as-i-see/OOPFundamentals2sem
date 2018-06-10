#include "loader.h"
#include "ui_loader.h"
#include <QSqlRecord>
#include <QString>

Loader::Loader(QWidget *parent) : QMainWindow(parent), ui(new Ui::Loader) {
  ui->setupUi(this);
  connect(ui->pushButton, SIGNAL(clicked(bool)), this, SLOT(load()));
}

Loader::~Loader() { delete ui; }

void Loader::load() {
  QString tableName = ui->lineEdit->text();

  auto data = this->dbAccessor->load(tableName);

  emit sendData(data);
  this->close();
}

void Loader::setDBAccessor(DBAccessor *accessor) {
  this->dbAccessor = accessor;
}
