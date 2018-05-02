#ifndef SAVER_H
#define SAVER_H

#include "cube.h"
#include "dbaccessor.h"
#include "prism.h"
#include "vertex.h"
#include <QMainWindow>
#include <vector>

namespace Ui {
class Saver;
}

class Saver : public QMainWindow {
  Q_OBJECT

public:
  explicit Saver(QMainWindow *parent = 0);
  ~Saver();
  void setDBAccessor(DBAccessor *);
private slots:
  void persist();

signals:
  void dataUpdate(std::pair<std::vector<Cube>, std::vector<Prism>> &);

private:
  Ui::Saver *ui;
  DBAccessor *dbAccessor;
  void applyLiveTransformations(std::vector<Cube> &, std::vector<Prism> &);
};

#endif // SAVER_H
