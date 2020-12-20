#ifndef USAGEDATA6MODEL_H
#define USAGEDATA6MODEL_H

#include <QAbstractListModel>
#include <QHash>
#include <vector>
#include <memory>
#include <QDateTime>

#include "databasemanager.h"
#include "usagedata6.h"

class UsageData6Model : public QAbstractListModel
{
    Q_OBJECT
    Q_CLASSINFO("RegisterEnumClassesUnscoped", "false")
  public:

    enum Roles {
      DataIdRole = Qt::UserRole + 1,
      DataRole
    };

    UsageData6Model(QObject* parent =0);

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;


    Q_INVOKABLE void insert_data(QDateTime& timestamp, const QString& data);
    QModelIndex insert(const UsageData6& usagedata6);

    Q_INVOKABLE QVariantMap at(int row = 0) const;
    // Q_INVOKABLE void data();
    void refresh();

  private:
    bool isIndexValid(const QModelIndex& index) const;

  private:
    DatabaseManager& db_;
    std::unique_ptr<std::vector<std::unique_ptr<UsageData6>>> usagedata6_;
};

#endif // USAGEDATA6MODEL_H
