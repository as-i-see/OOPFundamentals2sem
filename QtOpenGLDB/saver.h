#ifndef SAVER_H
#define SAVER_H

#include <QMainWindow>
#include <QSqlQuery>
#include <QtSql>
#include <vector>
#include "cube.h"
#include "vertex.h"

namespace Ui {
class Saver;
}

class Saver : public QMainWindow {
  Q_OBJECT

 public:
  explicit Saver(QMainWindow *parent = 0);
  ~Saver();
 public slots:
  void setData(std::vector<Cube>);
 private slots:
  bool persist();

 private:
  Ui::Saver *ui;
  QSqlDatabase db;
  QSqlQuery *saveCubeVertex, *savePrismVertex;
  QString cubeTableName, prismTableName;
  std::vector<Cube> data;
};

#endif  // SAVER_H
