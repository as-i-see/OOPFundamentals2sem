#include "mainwindow.h"
#include <QDebug>
#include <iostream>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
  ui = new Ui::MainWindow;
  ui->setupUi(this);
  this->newActionForm = new NewActionForm(this);

  this->dbAccessor = new DBAccessor;
  this->saver = new Saver(this);
  this->saver->setDBAccessor(this->dbAccessor);
  this->loader = new Loader();
  this->loader->setDBAccessor(this->dbAccessor);
  this->scene = ui->openGLWidget;
  this->prefsEditor = new preferencesEditor();

  connect(ui->actionNew, &QAction::triggered, this->newActionForm,
          &NewActionForm::show);
  connect(ui->actionSave_as, &QAction::triggered, this->saver, &Saver::show);

  connect(ui->actionOpen, &QAction::triggered, this->loader, &Loader::show);
  connect(ui->actionEdition_setting, &QAction::triggered, this->prefsEditor,
          &preferencesEditor::show);

  connect(this->newActionForm,
          SIGNAL(creationCompleted(
              std::pair<std::vector<Cylinder>, std::vector<Prism>>)),
          this->scene,
          SLOT(loadScene(std::pair<std::vector<Cylinder>, std::vector<Prism>>)));
  connect(this->loader,
          SIGNAL(sendData(std::pair<std::vector<Cylinder>, std::vector<Prism>>)),
          this->scene,
          SLOT(loadScene(std::pair<std::vector<Cylinder>, std::vector<Prism>>)));
  connect(
      this->saver,
      SIGNAL(dataUpdate(std::pair<std::vector<Cylinder>, std::vector<Prism>> &)),
      this->scene,
      SLOT(sceneConfigRequest(
          std::pair<std::vector<Cylinder>, std::vector<Prism>> &)));

  connect(this->prefsEditor, SIGNAL(sendPrefs(std::vector<float>)), this->scene,
          SLOT(setPreferences(std::vector<float>)));
  setCentralWidget(ui->openGLWidget);

  this->scene->setFocus();

  this->toolBar = new ToolBar(this, this->scene);
  addToolBar(toolBar);
}

MainWindow::~MainWindow() {}
