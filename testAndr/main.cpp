#include "mainwindow.h"
#include "test.h"
#include <QApplication>
#include <QIcon>
#include <QtTest/Qtest>

int main(int argc, char *argv[]) {

  QApplication app(argc, argv);
  QTest::qExec(new Test, argc, argv);

  MainWindow mw;
  mw.show();

  return app.exec();
}
