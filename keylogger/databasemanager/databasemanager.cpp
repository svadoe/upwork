#include <QSqlDatabase>
#include <QFile>
#include <QStandardPaths>
#include <QSqlError>
#include <QDebug>

#include "databasemanager.h"
#include "simplecrypt.h"


#ifdef Q_OS_IOS

#include <QtPlugin>
#include <QSqlDatabase>

//Q_IMPORT_PLUGIN(qsqlite)
Q_IMPORT_PLUGIN(SqliteCipherDriverPlugin)

#endif

DatabaseManager& DatabaseManager::instance()
{
    qDebug() << DATABASE_FILENAME;
#if defined(Q_OS_ANDROID) || defined(Q_OS_IOS)
  // QFile assetDbFile(":/database/" + DATABASE_FILENAME);
  QString destinationDbFile = QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation).append("/" + DATABASE_FILENAME);
  QString destinationDbFile = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation).append("/" + DATABASE_FILENAME);
  if (!QFile::exists(destinationDbFile)) {
    assetDbFile.copy(destinationDbFile);
    QFile::setPermissions(destinationDbFile, QFile::WriteOwner | QFile::ReadOwner);
  }
  static DatabaseManager singleton(destinationDbFile);
#else
  static DatabaseManager singleton;
#endif
  return singleton;
}



DatabaseManager::DatabaseManager(const QString& path) :
  database_(new QSqlDatabase(QSqlDatabase::addDatabase("QSQLITE"))),
  // database_(new QSqlDatabase(QSqlDatabase::addDatabase("SQLITECIPHER"))),
  usagedata6Dao_(*database_)
{
  database_->setDatabaseName(path);

/* 
 *   //Set The Encryption And Decryption Key
 *   SimpleCrypt processSimpleCrypt(Q_UINT64_C(0x02c23bd0363ae9d5));
 *
 *   QString ab0x2("AwKQgX19zpE3V7RrNDSB3HgZ/C0kc5CfPA==");
 *
 *   QString decrypt = processSimpleCrypt.decryptToString(ab0x2);
 *   database_->setPassword(decrypt);
 *   database_->setConnectOptions("QSQLITE_USE_CIPHER=sqlcipher; QSQLITE_ENABLE_REGEXP");
 *  */

  if (!database_->open()) {
    qDebug() << "Database could not be opened";
    exit(-1);
  }

  usagedata6Dao_.init();
}

DatabaseManager::~DatabaseManager()
{
  database_->close();
  delete database_;
}
