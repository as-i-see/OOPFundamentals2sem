#include "mainwindow.h"
#include <QDebug>
#include <iostream>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
  ui = new Ui::MainWindow;
  ui->setupUi(this);
  this->newActionForm = new NewActionForm(this);

  QSqlDatabase::addDatabase("QPSQL");

  this->saver = new Saver(this);
  connect(ui->actionNew, &QAction::triggered, this->newActionForm,
          &NewActionForm::show);
  connect(ui->actionSave_as, &QAction::triggered, this->saver, &Saver::show);
  connect(this, SIGNAL(resendData(std::pair<std::vector<Cube>, int>)),
          this->saver, SLOT(setData(std::pair<std::vector<Cube>, int>)));

  this->loader = new Loader();
  connect(ui->actionOpen, &QAction::triggered, this->loader, &Loader::show);
  connect(this->loader, SIGNAL(sendData(std::pair<std::vector<Cube>, int>)),
          this, SLOT(loadNewScene(std::pair<std::vector<Cube>, int>)));

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
  emit resendData(figures);
}
