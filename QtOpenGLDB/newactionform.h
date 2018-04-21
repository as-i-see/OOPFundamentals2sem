#ifndef NEWACTIONFORM_H
#define NEWACTIONFORM_H

#include <QDebug>
#include <QLabel>
#include <QPushButton>
#include <QWidget>
#include "cube.h"
#include "cubecreation.h"

namespace Ui {
class NewActionForm;
}

class NewActionForm : public QWidget {
  Q_OBJECT

 public:
  explicit NewActionForm(QMainWindow *parent = 0);
  ~NewActionForm();
 signals:
  void creationCompleted(std::pair<std::vector<Cube>, int>);
 public slots:
  void creationCompleted();
  void newCubeReady(Cube);

 private:
  QMainWindow *parent;
  Ui::NewActionForm *ui;
  QLabel *cubesLabel, *prismsLabel;
  QPushButton *cubeButton, *submitButton;
  CubeCreation *cubeCreation;
  std::vector<Cube> cubes;
};

#endif  // NEWACTIONFORM_H
