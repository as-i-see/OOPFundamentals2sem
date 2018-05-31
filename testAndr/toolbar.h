#ifndef TOOLBAR_H
#define TOOLBAR_H

#include "scene.h"
#include <QIcon>
#include <QObject>
#include <QToolBar>

class ToolBar : public QToolBar {
  Q_OBJECT
public:
  ToolBar(QWidget *, Scene *);

private:
  QAction *play;
  Scene *scene;
};

#endif // TOOLBAR_H
