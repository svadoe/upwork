#ifndef USAGEDATA6_H
#define USAGEDATA6_H

#include <QString>
#include <QDateTime>

class UsageData6
{
  public:
    explicit UsageData6();

    QDateTime data_id_{-1};
    QString data_{-1};
};

#endif // USAGEDATA6_H
