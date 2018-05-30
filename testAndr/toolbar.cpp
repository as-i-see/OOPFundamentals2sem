#include "toolbar.h"

ToolBar::ToolBar(QWidget *parent, Scene *scene)
    : QToolBar(parent), scene(scene) {
  //  this->lineEdit = new QLineEdit();
  //  this->lineEdit->setAlignment(Qt::AlignCenter);
  //  this->lineEdit->setStyleSheet("font: bold 32px");
  //  this->addWidget(this->lineEdit);
  this->setIconSize(QSize(75, 75));
  this->setMovable(false);
  this->play = new QAction(QIcon(":/images/play.png"), QString("Start"), this);
  connect(this->play, SIGNAL(triggered(bool)), this->scene, SLOT(start()));
  this->addAction(this->play);
}
