#ifndef USAGEDATA6DAO_H
#define USAGEDATA6DAO_H

#include <vector>
#include <memory>

class QSqlDatabase;
class UsageData6;

class UsageData6Dao
{
  public:
    UsageData6Dao(QSqlDatabase& database);
    void init() const;
    std::unique_ptr<std::vector<std::unique_ptr<UsageData6>>> usagedata6() const;

  private:
    QSqlDatabase& database_;
};

#endif // USAGEDATA6DAO_H
