#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QAction>
#include <QMainWindow>
#include "cube.h"
#include "newactionform.h"
#include "saver.h"
#include "toolbar.h"
#include "ui_mainwindow.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = 0);
  ~MainWindow();
 signals:
  void sceneChanged();
  void resendData(std::vector<Cube>);
 public slots:
  void loadNewScene(std::pair<std::vector<Cube>,
                              int>);  // TODO: second argument would be prisms
 private slots:
  void on_actionMultiple_figure_selection_toggled(bool arg1);

  void on_actionMultiple_face_selection_toggled(bool arg1);

 private:
  Ui::MainWindow *ui;
  NewActionForm *newActionForm;
  Saver *saver;
  Scene *scene;
  ToolBar *toolBar;
};

#endif  // MAINWINDOW_H
