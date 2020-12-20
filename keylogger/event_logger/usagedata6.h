#ifndef USAGEDATA6_H
#define USAGEDATA6_H

#include <QString>
#include <QDateTime>

class UsageData6
{
  public:
    explicit UsageData6(const QDateTime& data_id = QDateTime::currentDateTimeUtc(), const QString& data="");

    QDateTime data_id_;
    QString data_;
};

#endif // USAGEDATA6_H
