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

  this->loader = new Loader();
  this->scene = ui->openGLWidget;
  connect(ui->actionOpen, &QAction::triggered, this->loader, &Loader::show);

  connect(this->newActionForm,
          SIGNAL(creationCompleted(
              std::pair<std::vector<Cube>, std::vector<Prism>>)),
          this->scene,
          SLOT(loadScene(std::pair<std::vector<Cube>, std::vector<Prism>>)));
  connect(this->loader,
          SIGNAL(sendData(std::pair<std::vector<Cube>, std::vector<Prism>>)),
          this->scene,
          SLOT(loadScene(std::pair<std::vector<Cube>, std::vector<Prism>>)));
  connect(
      this->saver,
      SIGNAL(dataUpdate(std::pair<std::vector<Cube>, std::vector<Prism>> &)),
      this->scene,
      SLOT(sceneConfigRequest(
          std::pair<std::vector<Cube>, std::vector<Prism>> &)));
  setCentralWidget(ui->openGLWidget);

  this->scene->setFocus();

  this->toolBar = new ToolBar(this, this->scene);
  addToolBar(toolBar);
}

MainWindow::~MainWindow() {}
