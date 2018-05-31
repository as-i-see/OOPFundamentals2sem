#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QApplication>
#include <QScreen>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  this->scene = new Scene();
  setCentralWidget(this->scene);
  this->toolBar = new ToolBar(this, this->scene);
  this->addToolBar(this->toolBar);
}

MainWindow::~MainWindow() { delete ui; }
