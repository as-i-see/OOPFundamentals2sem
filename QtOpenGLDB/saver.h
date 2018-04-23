#ifndef SAVER_H
#define SAVER_H

#include "cube.h"
#include "prism.h"
#include "vertex.h"
#include <QMainWindow>
#include <QSqlQuery>
#include <QtSql>
#include <vector>

namespace Ui {
class Saver;
}

class Saver : public QMainWindow {
  Q_OBJECT

public:
  explicit Saver(QMainWindow *parent = 0);
  ~Saver();
private slots:
  bool persist();

signals:
  void dataUpdate(std::pair<std::vector<Cube>, std::vector<Prism>> &);

private:
  Ui::Saver *ui;
  QSqlDatabase db;
  QSqlQuery *saveCubeVertex, *savePrismVertex;
  QString cubeTableName, prismTableName;
  std::vector<Cube> cubes;
  std::vector<Prism> prisms;
  void applyLiveTransformations();
};

#endif // SAVER_H
