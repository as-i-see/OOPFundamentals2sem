#include "toolbar.h"

ToolBar::ToolBar(QWidget *parent, Scene *scene)
    : QToolBar(parent), scene(scene) {
  this->setIconSize(QSize(150, 150));
  this->setMovable(false);
  this->restart =
      new QAction(QIcon(":/images/restart.png"), QString("Restart"), this);
  connect(this->restart, SIGNAL(triggered(bool)), this->scene, SLOT(restart()));
  this->addAction(this->restart);
  this->slider = new QSlider(Qt::Horizontal);
  slider->setMaximum(0);
  slider->setMaximum(10);
  slider->setValue(10);
  slider->setSingleStep(1);
  slider->setTickPosition(QSlider::TicksBothSides);
  slider->setTickInterval(1);
  connect(slider, SIGNAL(valueChanged(int)), this->scene,
          SLOT(setElasticFactor(int)));
  this->addWidget(slider);
  this->setStyleSheet("padding: 30px;"
                      "spacing: 30px");
}
