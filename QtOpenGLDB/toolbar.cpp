#include "toolbar.h"

ToolBar::ToolBar(QWidget* parent) : QToolBar(parent) {}

ToolBar::ToolBar(QWidget* parent, Scene* glWidget) : QToolBar(parent) {
  xRotationAction =
      new QAction(QIcon(":/images/x-rotation.jpg"), QString("X-rotate"), this);
  connect(xRotationAction, SIGNAL(triggered(bool)), glWidget, SLOT(rotateX()));
  addAction(xRotationAction);

  yRotationAction =
      new QAction(QIcon(":/images/y-rotation.jpg"), QString("Y-rotate"), this);
  connect(yRotationAction, SIGNAL(triggered(bool)), glWidget, SLOT(rotateY()));
  addAction(yRotationAction);

  zRotationAction =
      new QAction(QIcon(":/images/z-rotation.jpg"), QString("Z-rotate"), this);
  connect(zRotationAction, SIGNAL(triggered(bool)), glWidget, SLOT(rotateZ()));
  addAction(zRotationAction);

  addSeparator();

  xyProjectionAction = new QAction(QIcon(":/images/plane-xy-proj.jpg"),
                                   QString("XY-projection"), this);
  connect(xyProjectionAction, SIGNAL(triggered(bool)), glWidget,
          SLOT(showXYProjection()));
  addAction(xyProjectionAction);

  yzProjectionAction = new QAction(QIcon(":/images/plane-yz-proj.jpg"),
                                   QString("YZ-projection"), this);
  connect(yzProjectionAction, SIGNAL(triggered(bool)), glWidget,
          SLOT(showYZProjection()));
  addAction(yzProjectionAction);

  zxProjectionAction = new QAction(QIcon(":/images/plane-zx-proj.jpg"),
                                   QString("ZX-projection"), this);
  connect(zxProjectionAction, SIGNAL(triggered(bool)), glWidget,
          SLOT(showZXProjection()));
  addAction(zxProjectionAction);

  addSeparator();

  xLeftAction =
      new QAction(QIcon(":/images/x_left.jpg"), QString("Left"), this);
  connect(xLeftAction, SIGNAL(triggered(bool)), glWidget, SLOT(moveLeft()));
  addAction(xLeftAction);

  xRightAction =
      new QAction(QIcon(":/images/x_right.jpg"), QString("Right"), this);
  connect(xRightAction, SIGNAL(triggered(bool)), glWidget, SLOT(moveRight()));
  addAction(xRightAction);

  yLeftAction =
      new QAction(QIcon(":/images/y_left.jpg"), QString("Down"), this);
  connect(yLeftAction, SIGNAL(triggered(bool)), glWidget, SLOT(moveDown()));
  addAction(yLeftAction);

  yRightAction =
      new QAction(QIcon(":/images/y_right.jpg"), QString("Up"), this);
  connect(yRightAction, SIGNAL(triggered(bool)), glWidget, SLOT(moveUp()));
  addAction(yRightAction);

  zLeftAction =
      new QAction(QIcon(":/images/z_left.jpg"), QString("Backward"), this);
  connect(zLeftAction, SIGNAL(triggered(bool)), glWidget, SLOT(moveBackward()));
  addAction(zLeftAction);

  zRightAction =
      new QAction(QIcon(":/images/z_right.jpg"), QString("Frontward"), this);
  connect(zRightAction, SIGNAL(triggered(bool)), glWidget,
          SLOT(moveFrontward()));
  addAction(zRightAction);
}

ToolBar::~ToolBar() {
  delete xRotationAction;
  delete yRotationAction;
  delete zRotationAction;
  delete xyProjectionAction;
  delete yzProjectionAction;
  delete zxProjectionAction;
  delete xLeftAction;
  delete xRightAction;
  delete yLeftAction;
  delete yRightAction;
  delete zLeftAction;
  delete zRightAction;
}
