#ifndef SERVER_H
#define SERVER_H

#include "thread.h"
#include <QStringList>
#include <QTcpServer>

class Server : public QTcpServer {
  Q_OBJECT

public:
  Server(QObject *parent = 0);

protected:
  void incomingConnection(qintptr socketDescriptor) override;

private:
  QStringList fortunes;
};

#endif // SERVER_H
