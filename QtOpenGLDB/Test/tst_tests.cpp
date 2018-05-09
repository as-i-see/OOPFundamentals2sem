#include <QObject>
#include <QSqlQuery>
#include <QtSql>
#include <QtTest>
#include <iostream>
#include <vector>
// add necessary includes here

class Tests : public QObject {
  Q_OBJECT

public:
  Tests();
  ~Tests();

private slots:
  void driverAvailability();
  void dbConnectivity();
  void tableCreation();
  void recordsCreation();
  void recordsReading();
  void cleanupTestCase();
};

Tests::Tests() {}

Tests::~Tests() {}

void Tests::driverAvailability() {
  QSqlDatabase::addDatabase("QPSQL");
  QVERIFY(QSqlDatabase::database().isValid() == true);
}

void Tests::dbConnectivity() {
  QSqlDatabase db = QSqlDatabase::database();
  db.setHostName("localhost");
  db.setDatabaseName("postgres");
  db.setUserName("postgres");
  db.setPort(5432);
  db.open();
  QVERIFY(db.isOpenError() == false);
}

void Tests::tableCreation() {
  QSqlQuery query(QSqlDatabase::database());
  bool successfully = query.exec("CREATE TABLE test ("
                                 " x NUMERIC(6,0) "
                                 ")");
  QVERIFY(successfully == true);
}

void Tests::recordsCreation() {
  QSqlQuery query(QSqlDatabase::database());
  bool successfully = query.exec("INSERT INTO test VALUES (1325)") &&
                      query.exec("INSERT INTO test VALUES (1426)");
  QVERIFY(successfully == true);
}

void Tests::recordsReading() {
  QSqlQuery query(QSqlDatabase::database());
  bool successfully = query.exec("SELECT * FROM test");
  QVERIFY(successfully == true);
  std::vector<int> res;
  while (query.next()) {
    res.push_back(query.value(0).toInt());
  }
  QVERIFY(res.size() == 2);
  QVERIFY(res[0] == 1325);
  QVERIFY(res[1] == 1426);
}

void Tests::cleanupTestCase() {
  QSqlQuery query(QSqlDatabase::database());
  bool successfully = query.exec("DROP TABLE test;");
  QVERIFY(successfully == true);
  QSqlDatabase db = QSqlDatabase::database();
  db.close();
  QVERIFY(db.isOpen() == false);
}

QTEST_APPLESS_MAIN(Tests)

#include "tst_tests.moc"
