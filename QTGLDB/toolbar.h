#ifndef TOOLBAR_H
#define TOOLBAR_H

#include "scene.h"
#include <QIcon>
#include <QToolBar>

class ToolBar : public QToolBar {
  Q_OBJECT

private:
  QAction *xRotationAction;
  QAction *yRotationAction;
  QAction *zRotationAction;
  QAction *xyProjectionAction;
  QAction *yzProjectionAction;
  QAction *zxProjectionAction;
  QAction *xRightAction;
  QAction *xLeftAction;
  QAction *yRightAction;
  QAction *yLeftAction;
  QAction *zRightAction;
  QAction *zLeftAction;
  QAction *scaleAction;
  QAction *pickColorAction;

public:
  ToolBar(QWidget *);
  ToolBar(QWidget *, Scene *);
  ~ToolBar();
};

#endif // TOOLBAR_H
