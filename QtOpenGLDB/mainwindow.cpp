#include "mainwindow.h"
#include <QDebug>
#include <iostream>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
  ui = new Ui::MainWindow;
  ui->setupUi(this);
  this->newActionForm = new NewActionForm(this);
  this->saver = new Saver(this);
  connect(ui->actionNew, &QAction::triggered, this->newActionForm,
          &NewActionForm::show);
  connect(ui->actionSave_as, &QAction::triggered, this->saver, &Saver::show);
  connect(this, SIGNAL(resendData(std::vector<Cube>)), this->saver,
          SLOT(setData(std::vector<Cube>)));
  setCentralWidget(ui->openGLWidget);
  this->scene = ui->openGLWidget;
  this->scene->setFocus();
  connect(this, SIGNAL(sceneChanged()), this->scene, SLOT(reloadScene()));
  this->toolBar = new ToolBar(this, this->scene);
  addToolBar(toolBar);
}

MainWindow::~MainWindow() {}

void MainWindow::loadNewScene(std::pair<std::vector<Cube>, int> figures) {
  this->scene->cubes = figures.first;
  emit sceneChanged();
  emit resendData(figures.first);
}

void MainWindow::on_actionMultiple_figure_selection_toggled(bool arg1) {
  this->scene->multipleFigureMode = arg1;
}

void MainWindow::on_actionMultiple_face_selection_toggled(bool arg1) {
  this->scene->multipleFaceMode = arg1;
}
