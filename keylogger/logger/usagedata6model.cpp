#include "usagedata6model.h"

UsageData6Model::UsageData6Model(QObject* parent) :
  QAbstractListModel(parent),
  db_(DatabaseManager::instance()),
  usagedata6_(db_.usagedata6Dao_.usagedata6())
{
}


int UsageData6Model::rowCount(const QModelIndex& parent) const
{
  return usagedata6_->size();
}

QVariant UsageData6Model::data(const QModelIndex& index, int role) const
{
  if (!isIndexValid(index)) {
    return QVariant();
  }
  const UsageData6& usagedata6 = *usagedata6_->at(index.row());

  switch (role) {
    case Roles::DataIdRole:
      return usagedata6.data_id_;
    case Roles::DataRole:
      return usagedata6.data_;
    case Qt::DisplayRole:
      return usagedata6.data_id_;
    default:
      return QVariant();
  }
}


QHash<int, QByteArray> UsageData6Model::roleNames() const
{
  QHash<int, QByteArray> roles;
  roles[Roles::DataIdRole] = "data_id";
  roles[Roles::DataRole] = "data";
  return roles;
}


void UsageData6Model::insert_data(QDateTime& timestamp, const QString& data)
{
  insert(UsageData6(timestamp, data));
}


QModelIndex UsageData6Model::insert(const UsageData6& usagedata6)
{
  int rowIndex = rowCount();

  beginInsertRows(QModelIndex(), rowIndex, rowIndex);
    std::unique_ptr<UsageData6> new_usage_data(new UsageData6(usagedata6));
    db_.usagedata6Dao_.insert(*new_usage_data);
    usagedata6_->push_back(move(new_usage_data));
  endInsertRows();

  return index(rowIndex, 0);
}


QVariantMap UsageData6Model::at(int row) const
{
  QHash<int, QByteArray> names = roleNames();
  QHashIterator<int, QByteArray>  i(names);
  QVariantMap res;
  while(i.hasNext()) {
    i.next();
    QModelIndex idx = index(row, 0);
    QVariant data = idx.data(i.key());
    res[i.value()] = data;
  }
  return res;
}

bool UsageData6Model::isIndexValid(const QModelIndex& index) const
{
  if (index.row() < 0 ||
      index.row() >= rowCount() ||
      !index.isValid()) {
    return false;
  }
  return true;
}


// void UsageData6Model::refresh(int test_id)
void UsageData6Model::refresh()
{
  beginResetModel();
  usagedata6_ = db_.usagedata6Dao_.usagedata6();
  endResetModel();

  QModelIndex index;
  emit dataChanged(index, index);
}

/* 
 * void UsageData6Model::usagedata6(int test_id)
 * {
 *   refresh(test_id);
 * }
 *  */

/* 
 * QVariantList UsageData6Model::data() const
 * {
 *   return db_.usagedata6Dao_.usagedata6s();
 * }
 *  */
