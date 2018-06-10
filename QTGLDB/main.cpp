#include "cylinder.h"
#include "mainwindow.h"
#include "transform3d.h"
#include <QApplication>
int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  MainWindow w;
  w.show();
  return a.exec();
}
