#ifndef NEWACTIONFORM_H
#define NEWACTIONFORM_H

#include "cube.h"
#include "cubecreation.h"
#include "prism.h"
#include "prismcreation.h"
#include <QDebug>
#include <QLabel>
#include <QPushButton>
#include <QWidget>

namespace Ui {
class NewActionForm;
}

class NewActionForm : public QWidget {
  Q_OBJECT

public:
  explicit NewActionForm(QMainWindow *parent = 0);
  ~NewActionForm();
signals:
  void creationCompleted(std::pair<std::vector<Cube>, std::vector<Prism>>);
public slots:
  void creationCompleted();
  void newCubeReady(Cube);
  void newPrismReady(Prism);

private:
  QMainWindow *parent;
  Ui::NewActionForm *ui;
  QLabel *cubesLabel, *prismsLabel;
  QPushButton *cubeButton, *prismButton, *submitButton;
  CubeCreation *cubeCreation;
  PrismCreation *prismCreation;
  std::vector<Cube> cubes;
  std::vector<Prism> prisms;
};

#endif // NEWACTIONFORM_H
