#include "mainwindow.h"
#include "collisionsmaster.h"
#include "ui_mainwindow.h"
#include <QApplication>
#include <QScreen>
#include <QSlider>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  this->scene = new Scene();
  setCentralWidget(this->scene);
  // this->toolBar = new ToolBar(this, this->scene);
  this->toolBar = new QToolBar;
  this->toolBar->setIconSize(QSize(150, 150));
  this->toolBar->setMovable(false);
  this->toolBar->setStyleSheet("padding: 30px;"
                               "spacing: 30px");
  QAction *restart =
      new QAction(QIcon(":/images/restart.png"), QString("Restart"), this);
  connect(restart, SIGNAL(triggered(bool)), this->scene, SLOT(restart()));
  this->toolBar->addAction(restart);

  QSlider *slider = new QSlider(Qt::Horizontal);
  slider->setMaximum(0);
  slider->setMaximum(10);
  slider->setValue(10);
  slider->setSingleStep(1);
  slider->setTickPosition(QSlider::TicksBothSides);
  slider->setTickInterval(1);
  connect(slider, SIGNAL(valueChanged(int)), this->scene,
          SLOT(setElasticFactor(int)));
  this->toolBar->addWidget(slider);

  this->addToolBar(this->toolBar);
}

MainWindow::~MainWindow() { delete ui; }
