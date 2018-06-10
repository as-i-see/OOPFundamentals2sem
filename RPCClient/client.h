#ifndef CLIENT_H
#define CLIENT_H
#include <QComboBox>
#include <QDataStream>
#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QMessageBox>
#include <QNetworkSession>
#include <QPushButton>
#include <QTcpSocket>
#include <QTimer>

class QComboBox;
class QLabel;
class QLineEdit;
class QPushButton;
class QTcpSocket;
class QNetworkSession;

class Client : public QDialog {
  Q_OBJECT

public:
  explicit Client(QWidget *parent = nullptr);

private slots:
  void requestNewConsole();
  void displayError(QAbstractSocket::SocketError socketError);
  void enableConnectButton();
  void sessionOpened();

private:
  QComboBox *hostCombo = nullptr;
  QLineEdit *portLineEdit = nullptr;
  QLabel *statusLabel = nullptr;
  QPushButton *connectButton = nullptr;

  QTcpSocket *tcpSocket = nullptr;

  QNetworkSession *networkSession = nullptr;
};

#endif // CLIENT_H
