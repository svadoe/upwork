#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QString>

#include "usagedata6dao.h"

class QSqlDatabase;

const QString DATABASE_FILENAME = "database.db";
//const QString DATABASE_FILENAME = "database_.db";

class DatabaseManager
{
  public:
    static DatabaseManager& instance();
    ~DatabaseManager();

  protected:
    DatabaseManager(const QString& path = DATABASE_FILENAME);
    DatabaseManager& operator =(const DatabaseManager& rhs);

  private:
    QSqlDatabase* database_;

  public:
    const UsageData6Dao usagedata6Dao_;
};

#endif // DATABASEMANAGER_H
