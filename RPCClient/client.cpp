#include <QtNetwork>
#include <QtWidgets>

#include "client.h"

Client::Client(QWidget *parent)
    : QDialog(parent), hostCombo(new QComboBox), portLineEdit(new QLineEdit),
      connectButton(new QPushButton(tr("New Console"))),
      tcpSocket(new QTcpSocket(this)) {
  setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
  hostCombo->setEditable(true);
  // find out name of this machine
  QString name = QHostInfo::localHostName();
  if (!name.isEmpty()) {
    hostCombo->addItem(name);
    QString domain = QHostInfo::localDomainName();
    if (!domain.isEmpty())
      hostCombo->addItem(name + QChar('.') + domain);
  }
  if (name != QLatin1String("localhost"))
    hostCombo->addItem(QString("localhost"));
  // find out IP addresses of this machine
  QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
  // add non-localhost addresses
  for (int i = 0; i < ipAddressesList.size(); ++i) {
    if (!ipAddressesList.at(i).isLoopback())
      hostCombo->addItem(ipAddressesList.at(i).toString());
  }
  // add localhost addresses
  for (int i = 0; i < ipAddressesList.size(); ++i) {
    if (ipAddressesList.at(i).isLoopback())
      hostCombo->addItem(ipAddressesList.at(i).toString());
  }

  portLineEdit->setValidator(new QIntValidator(1, 65535, this));

  auto hostLabel = new QLabel(tr("&Server name:"));
  hostLabel->setBuddy(hostCombo);
  auto portLabel = new QLabel(tr("S&erver port:"));
  portLabel->setBuddy(portLineEdit);

  statusLabel = new QLabel(tr("This program requires that you run the "
                              "RPCServer as well."));

  connectButton->setDefault(true);
  connectButton->setEnabled(false);

  auto quitButton = new QPushButton(tr("Quit"));

  auto buttonBox = new QDialogButtonBox;
  buttonBox->addButton(connectButton, QDialogButtonBox::ActionRole);
  buttonBox->addButton(quitButton, QDialogButtonBox::RejectRole);

  connect(hostCombo, &QComboBox::editTextChanged, this,
          &Client::enableConnectButton);
  connect(portLineEdit, &QLineEdit::textChanged, this,
          &Client::enableConnectButton);
  connect(connectButton, &QAbstractButton::clicked, this,
          &Client::requestNewConsole);
  connect(quitButton, &QAbstractButton::clicked, this, &QWidget::close);
  connect(tcpSocket,
          QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::error),
          this, &Client::displayError);

  QGridLayout *mainLayout = nullptr;
  if (QGuiApplication::styleHints()->showIsFullScreen() ||
      QGuiApplication::styleHints()->showIsMaximized()) {
    auto outerVerticalLayout = new QVBoxLayout(this);
    outerVerticalLayout->addItem(new QSpacerItem(
        0, 0, QSizePolicy::Ignored, QSizePolicy::MinimumExpanding));
    auto outerHorizontalLayout = new QHBoxLayout;
    outerHorizontalLayout->addItem(new QSpacerItem(
        0, 0, QSizePolicy::MinimumExpanding, QSizePolicy::Ignored));
    auto groupBox = new QGroupBox(QGuiApplication::applicationDisplayName());
    mainLayout = new QGridLayout(groupBox);
    outerHorizontalLayout->addWidget(groupBox);
    outerHorizontalLayout->addItem(new QSpacerItem(
        0, 0, QSizePolicy::MinimumExpanding, QSizePolicy::Ignored));
    outerVerticalLayout->addLayout(outerHorizontalLayout);
    outerVerticalLayout->addItem(new QSpacerItem(
        0, 0, QSizePolicy::Ignored, QSizePolicy::MinimumExpanding));
  } else {
    mainLayout = new QGridLayout(this);
  }
  mainLayout->addWidget(hostLabel, 0, 0);
  mainLayout->addWidget(hostCombo, 0, 1);
  mainLayout->addWidget(portLabel, 1, 0);
  mainLayout->addWidget(portLineEdit, 1, 1);
  mainLayout->addWidget(statusLabel, 2, 0, 1, 2);
  mainLayout->addWidget(buttonBox, 3, 0, 1, 2);

  setWindowTitle(QGuiApplication::applicationDisplayName());
  portLineEdit->setFocus();

  QNetworkConfigurationManager manager;
  if (manager.capabilities() &
      QNetworkConfigurationManager::NetworkSessionRequired) {
    // Get saved network configuration
    QSettings settings(QSettings::UserScope, QLatin1String("QtProject"));
    settings.beginGroup(QLatin1String("QtNetwork"));
    const QString id =
        settings.value(QLatin1String("DefaultNetworkConfiguration")).toString();
    settings.endGroup();

    // If the saved network configuration is not currently discovered use the
    // system default
    QNetworkConfiguration config = manager.configurationFromIdentifier(id);
    if ((config.state() & QNetworkConfiguration::Discovered) !=
        QNetworkConfiguration::Discovered) {
      config = manager.defaultConfiguration();
    }

    networkSession = new QNetworkSession(config, this);
    connect(networkSession, &QNetworkSession::opened, this,
            &Client::sessionOpened);

    connectButton->setEnabled(false);
    statusLabel->setText(tr("Opening network session."));
    networkSession->open();
  }
}

void Client::requestNewConsole() {
  connectButton->setEnabled(false);
  tcpSocket->abort();
  tcpSocket->connectToHost(hostCombo->currentText(),
                           portLineEdit->text().toInt());
}

void Client::displayError(QAbstractSocket::SocketError socketError) {
  switch (socketError) {
  case QAbstractSocket::RemoteHostClosedError:
    break;
  case QAbstractSocket::HostNotFoundError:
    QMessageBox::information(this, tr("RPCClient"),
                             tr("The host was not found. Please check the "
                                "host name and port settings."));
    break;
  case QAbstractSocket::ConnectionRefusedError:
    QMessageBox::information(this, tr("RPCClient"),
                             tr("The connection was refused by the peer. "
                                "Make sure the RPCServer is running, "
                                "and check that the host name and port "
                                "settings are correct."));
    break;
  default:
    QMessageBox::information(
        this, tr("RPCClient"),
        tr("The following error occurred: %1.").arg(tcpSocket->errorString()));
  }

  connectButton->setEnabled(true);
}

void Client::enableConnectButton() {
  connectButton->setEnabled((!networkSession || networkSession->isOpen()) &&
                            !hostCombo->currentText().isEmpty() &&
                            !portLineEdit->text().isEmpty());
}

void Client::sessionOpened() {
  // Save the used configuration
  QNetworkConfiguration config = networkSession->configuration();
  QString id;
  if (config.type() == QNetworkConfiguration::UserChoice)
    id = networkSession
             ->sessionProperty(QLatin1String("UserChoiceConfiguration"))
             .toString();
  else
    id = config.identifier();

  QSettings settings(QSettings::UserScope, QLatin1String("QtProject"));
  settings.beginGroup(QLatin1String("QtNetwork"));
  settings.setValue(QLatin1String("DefaultNetworkConfiguration"), id);
  settings.endGroup();

  statusLabel->setText(tr("This requires that you run the "
                          "PRCServer as well."));

  enableConnectButton();
}
