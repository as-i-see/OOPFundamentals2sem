#ifndef PRISMCREATION_H
#define PRISMCREATION_H

#include "prism.h"
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
class PrismCreation;
}

class PrismCreation : public QMainWindow {
  Q_OBJECT

public:
  explicit PrismCreation(QWidget *parent = 0);
  ~PrismCreation();

signals:
  void newPrismReady(Prism);

private slots:
  void on_pushButton_clicked(bool checked);

private:
  Ui::PrismCreation *ui;
  QLabel *dotLetter;
  int nDotsRead;
  QColor colors[6] = {Qt::red,   Qt::magenta, Qt::blue,
                      Qt::green, Qt::yellow,  Qt::cyan};
  std::vector<std::string> dots = {"A", "B", "C", "D", "E", "A1"};
  QPalette *currentPalette;
  QLineEdit *x, *y, *z;
  Prism prism;
  QRegExp *floatRegExp;
};

#endif // PRISMCREATION_H
