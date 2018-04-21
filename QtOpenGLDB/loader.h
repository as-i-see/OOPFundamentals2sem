#ifndef LOADER_H
#define LOADER_H

#include "cube.h"
#include <QMainWindow>
#include <QSqlQuery>
#include <QtSql>
#include <vector>

namespace Ui {
class Loader;
}

class Loader : public QMainWindow {
  Q_OBJECT

public:
  explicit Loader(QWidget *parent = 0);
  ~Loader();
public slots:
  void load();
signals:
  void sendData(std::pair<std::vector<Cube>, int>);

private:
  Ui::Loader *ui;
  QSqlDatabase db;
  QString cubeTableName, prismTableName;
  std::vector<Cube> cubes;
};

#endif // LOADER_H
