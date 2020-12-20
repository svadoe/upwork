#include <QSqlDatabase>
#include <QSqlQuery>
#include <QStringList>
#include <QVariant>

#include "usagedata6dao.h"
#include "databasemanager.h"
#include "usagedata6.h"

#include <QSqlError>


UsageData6Dao::UsageData6Dao(QSqlDatabase& database) :
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




void UsageData6Dao::insert(UsageData6& usagedata6) const
{
  QSqlQuery query(database_);
  query.prepare("INSERT INTO usagedata6 (dataId, data) VALUES ((:data_id),(:data))");
  query.bindValue(":data_id", usagedata6.data_id_);
  query.bindValue(":data", usagedata6.data_);
  query.exec();
}


std::unique_ptr<std::vector<std::unique_ptr<UsageData6>>> UsageData6Dao::usagedata6(/*QDateTime& start_date, QDateTime& end_date*/) const
{
  QSqlQuery query(database_);
  QString qry = "SELECT dataId, data FROM usagedata6 WHERE data_id BETWEEN :start_date AND end_date";
  /*
  QString qry = "SELECT dataId, data FROM usagedata6 WHERE data_id BETWEEN :start_date AND end_date";
  query.prepare(qry);
  query.bindValue(":start_date", start_date);
  query.bindValue(":end_date",);
  */
  query.exec();

  std::unique_ptr<std::vector<std::unique_ptr<UsageData6>>> list(new std::vector<std::unique_ptr<UsageData6>>());
  
  while (query.next()) {
    std::unique_ptr<UsageData6> usagedata6(new UsageData6());

    usagedata6->data_id_ = query.value("dataId").toDateTime();
    usagedata6->data_    = query.value("data").toString();

    list->push_back(move(usagedata6));
  }
  return list;
}


