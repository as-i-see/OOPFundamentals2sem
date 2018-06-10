#include "client.h"
#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  MainWindow w;
  Client client;
  client.show();

  return a.exec();
}
