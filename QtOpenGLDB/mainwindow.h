#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "cube.h"
#include "loader.h"
#include "newactionform.h"
#include "saver.h"
#include "toolbar.h"
#include "ui_mainwindow.h"
#include <QAction>
#include <QMainWindow>
#include <QSqlDatabase>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  MainWindow(QWidget *parent = 0);
  ~MainWindow();

private:
  Ui::MainWindow *ui;
  NewActionForm *newActionForm;
  Saver *saver;
  Loader *loader;
  Scene *scene;
  ToolBar *toolBar;
};

#endif // MAINWINDOW_H
