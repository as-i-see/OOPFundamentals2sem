#ifndef TOOLBAR_H
#define TOOLBAR_H

#include "scene.h"
#include <QIcon>
#include <QLineEdit>
#include <QObject>
#include <QToolBar>

class ToolBar : public QToolBar {
  Q_OBJECT
public:
  ToolBar(QWidget *, Scene *);

private:
  //  QLineEdit *lineEdit;
  QAction *play;
  Scene *scene;
};

#endif // TOOLBAR_H
