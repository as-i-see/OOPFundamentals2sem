#include "server.h"

#include <QRandomGenerator>

#include <stdlib.h>

Server::Server(QObject *parent) : QTcpServer(parent) {}

void Server::incomingConnection(qintptr socketDescriptor) {
  system("start cmd.exe");
}
