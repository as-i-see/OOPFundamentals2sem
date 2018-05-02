#ifndef LOADER_H
#define LOADER_H

#include "cube.h"
#include "dbaccessor.h"
#include "prism.h"
#include <QMainWindow>
#include <vector>

namespace Ui {
class Loader;
}

class Loader : public QMainWindow {
  Q_OBJECT

public:
  explicit Loader(QWidget *parent = 0);
  ~Loader();
  void setDBAccessor(DBAccessor *);
public slots:
  void load();
signals:
  void sendData(std::pair<std::vector<Cube>, std::vector<Prism>>);

private:
  Ui::Loader *ui;
  DBAccessor *dbAccessor;
};

#endif // LOADER_H
