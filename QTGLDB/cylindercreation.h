#ifndef CYLINDERCREATION_H
#define CYLINDERCREATION_H

#include "cylinder.h"
#include "ui_cylindercreation.h"
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
class CylinderCreation;
}

class CylinderCreation : public QMainWindow {
  Q_OBJECT

public:
  explicit CylinderCreation(QWidget *parent = 0);
  ~CylinderCreation();
signals:
  void newCylinderReady(Cylinder);
private slots:
  void on_pushButton_clicked(bool checked);

private:
  Ui::CylinderCreation *ui;
  QLabel *dotLetter;
  int nDotsRead;
  QColor colors[4] = {Qt::red, Qt::yellow, Qt::green, Qt::blue};
  std::vector<std::string> dots = {"A", "D", "B", "A1"};
  QPalette *currentPalette;
  QLineEdit *x, *y, *z;
  Cylinder cylinder;
  QRegExp *floatRegExp;
};

#endif // CUBECREATION_H
