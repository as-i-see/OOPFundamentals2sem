#ifndef CUBECREATION_H
#define CUBECREATION_H

#include "cube.h"
#include "vertex.h"
#include <QColor>
#include <QDebug>
#include <QLabel>
#include <QLineEdit>
#include <QMainWindow>
#include <QPalette>
#include <QRegExp>
#include <QValidator>
#include <string>
#include <vector>

namespace Ui {
class CubeCreation;
}

class CubeCreation : public QMainWindow {
  Q_OBJECT

public:
  explicit CubeCreation(QWidget *parent = 0);
  ~CubeCreation();
signals:
  void newCubeReady(Cube);
private slots:
  void on_pushButton_clicked(bool checked);

private:
  Ui::CubeCreation *ui;
  QLabel *dotLetter;
  int nDotsRead;
  QColor colors[4] = {Qt::red, Qt::yellow, Qt::green, Qt::blue};
  std::vector<std::string> dots = {"A", "D", "B", "A1"};
  QPalette *currentPalette;
  QLineEdit *x, *y, *z;
  Cube cube;
  QRegExp *floatRegExp;
};

#endif // CUBECREATION_H
