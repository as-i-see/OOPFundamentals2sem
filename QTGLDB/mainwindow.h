#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "cylinder.h"
#include "dbaccessor.h"
#include "loader.h"
#include "newactionform.h"
#include "preferenceseditor.h"
#include "saver.h"
#include "toolbar.h"
#include "ui_mainwindow.h"
#include <QAction>
#include <QMainWindow>

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
  DBAccessor *dbAccessor;
  Saver *saver;
  Loader *loader;
  Scene *scene;
  ToolBar *toolBar;
  preferencesEditor *prefsEditor;
};

#endif // MAINWINDOW_H
