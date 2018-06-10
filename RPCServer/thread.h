#ifndef THREAD_H
#define THREAD_H

#include <QTcpSocket>
#include <QThread>

class Thread : public QThread {
  Q_OBJECT

public:
  Thread(int socketDescriptor, const QString &fortune, QObject *parent);

  void run() override;

signals:
  void error(QTcpSocket::SocketError socketError);

private:
  int socketDescriptor;
  QString text;
};

#endif // THREAD_H
