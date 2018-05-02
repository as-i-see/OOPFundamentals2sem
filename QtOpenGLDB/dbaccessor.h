#ifndef DBACCESSOR_H
#define DBACCESSOR_H

#include "cube.h"
#include "prism.h"
#include <QObject>
#include <QSqlQuery>
#include <QtSql>

class DBAccessor : public QObject {
  Q_OBJECT
public:
  DBAccessor();
  void persist(QString, std::pair<std::vector<Cube>, std::vector<Prism>>);
  std::pair<std::vector<Cube>, std::vector<Prism>> load(QString);

private:
  QSqlDatabase db;
  QSqlQuery *saveCubeVertex, *savePrismVertex;
};

#endif // DBACCESSOR_H
