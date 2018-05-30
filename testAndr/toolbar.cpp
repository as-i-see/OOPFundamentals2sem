#include "toolbar.h"

ToolBar::ToolBar(QWidget *parent, Scene *scene)
    : QToolBar(parent), scene(scene) {
  this->setIconSize(QSize(375, 375));
  this->setMovable(false);
  this->play = new QAction(QIcon(":/images/play.png"), QString("Start"), this);
  connect(this->play, SIGNAL(triggered(bool)), this->scene, SLOT(start()));
  this->addAction(this->play);
}
