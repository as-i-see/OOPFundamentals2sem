#ifndef NEWACTIONFORM_H
#define NEWACTIONFORM_H

#include "cylinder.h"
#include "cylindercreation.h"
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
  void creationCompleted(std::pair<std::vector<Cylinder>, std::vector<Prism>>);
public slots:
  void creationCompleted();
  void newCubeReady(Cylinder);
  void newPrismReady(Prism);

private:
  QMainWindow *parent;
  Ui::NewActionForm *ui;
  QLabel *cubesLabel, *prismsLabel;
  QPushButton *cubeButton, *prismButton, *submitButton;
  CylinderCreation *cubeCreation;
  PrismCreation *prismCreation;
  std::vector<Cylinder> cubes;
  std::vector<Prism> prisms;
};

#endif // NEWACTIONFORM_H
