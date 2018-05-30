#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QApplication>
#include <QScreen>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  QScreen *screen = QApplication::screens().at(0);
  int WIDTH = screen->size().width();
  int HEIGHT = screen->size().height();

  this->scene = new Scene();
  setCentralWidget(this->scene);
  this->toolBar = new ToolBar(this, this->scene);
  this->addToolBar(this->toolBar);
}

MainWindow::~MainWindow() { delete ui; }
