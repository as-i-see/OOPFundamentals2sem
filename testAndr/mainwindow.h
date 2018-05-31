#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "scene.h"
#include "toolbar.h"
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

private:
  Ui::MainWindow *ui;
  QToolBar *toolBar;
  // ToolBar *toolBar;
  Scene *scene;
};

#endif // MAINWINDOW_H
