#include <QSqlDatabase>
#include <QSqlQuery>
#include <QStringList>
#include <QVariant>

#include "usagedata6dao.h"
#include "databasemanager.h"
#include "usagedata6.h"

#include <QSqlError>


UsageData6Dao::usagedata6Dao(QSqlDatabase& database) :
  database_(database)
{
}


void UsageData6Dao::init() const
{
  if (!database_.tables().contains("usagedata6")) {
    QSqlQuery query(database_);

    query.exec("CREATE TABLE usagedata6 (dataId TIMESTAMP PRIMARY KEY, data JSON)");
  }
}


std::unique_ptr<std::vector<std::unique_ptr<UsageData6>>> usagedata6Dao::usagedata6(QDateTime& start_date, QDateTime& end_date) const
{

  QSqlQuery query(database_);
  QString qry = "SELECT data_id, data FROM usagedata6 WHERE data_id BETWEEN :start_date AND end_date";
  query.prepare(qry);
  query.bindValue(":start_date", start_date);
  query.bindValue(":end_date",);
  query.exec();

  std::unique_ptr<std::vector<std::unique_ptr<UsageData6>>> list(new std::vector<std::unique_ptr<usagedata6>>());
  
  while (query.next()) {
    std::unique_ptr<UsageData6> usagedata6(new usagedata6());

    usagedata6->data_id        = query.value("test_id").toDateTime();
    usagedata6->data           = query.value("category_id").toString();

    list->push_back(move(usagedata6));
  }
  return list;
}


