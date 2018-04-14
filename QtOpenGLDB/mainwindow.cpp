#include "mainwindow.h"
#include <QDebug>
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    ui = new Ui::MainWindow;
    ui->setupUi(this);
    this->newActionForm = new NewActionForm(this);
    this->saver = new Saver(this);
    connect(ui->actionNew, &QAction::triggered, this->newActionForm, &NewActionForm::show);
    connect(ui->actionSave_as, &QAction::triggered, this->saver, &Saver::show);
    //connect(ui->actionSave_as, &QAction::triggered, this, &MainWindow::sendData);
    connect(this, SIGNAL(resendData(std::vector<std::vector<Vertex>>)), this->saver, SLOT(setData(std::vector<std::vector<Vertex> >)));
    setCentralWidget(ui->openGLWidget);
    this->scene = ui->openGLWidget;
    this->scene->setFocus();
    connect(this, SIGNAL(sceneChanged()), this->scene, SLOT(reloadScene()));
}

MainWindow::~MainWindow()
{

}

void MainWindow::loadNewScene(std::pair<std::vector<std::vector<Vertex>>, int> figures) {
    this->scene->figures = figures;
    emit sceneChanged();
    emit resendData(figures.first);
}
