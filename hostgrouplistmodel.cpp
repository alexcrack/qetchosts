#include "hostgrouplistmodel.h"

HostGroupListModel::HostGroupListModel(QObject *parent)
    : QAbstractListModel(parent)
{
    hostGroups = new QVector<HostsListItem*>();

    HostsListItem *item = new HostsListItem("Hello", "World", "hosts", true);
    hostGroups->push_back(item);

    HostsListItem *item2 = new HostsListItem("Foo", "Bar", "baz", false);
    hostGroups->push_back(item2);
}

int HostGroupListModel::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid())
        return 0;

    return hostGroups->size();
}

QVariant HostGroupListModel::data(const QModelIndex &index, int role) const
{
    int i = index.row();

    if (!index.isValid())
        return QVariant();

    if (role == Qt::DisplayRole) {
        return hostGroups->at(i)->name;
    }

    if (role == Qt::SizeHintRole) {
        return QSize(24, 24);
    }

    if (role == Qt::EditRole) {
        return hostGroups->at(i)->name;
    }

    if(role == Qt::CheckStateRole) {
        return hostGroups->at(i)->isActive ? Qt::Checked : Qt::Unchecked;
    }

    return QVariant();
}

bool HostGroupListModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (data(index, role) != value) {

        if (role == Qt::CheckStateRole) {
            hostGroups->at(index.row())->isActive = value.toBool();
        }

        if (role == Qt::EditRole) {
            hostGroups->at(index.row())->name = value.toString();
        }

        emit dataChanged(index, index, QVector<int>() << role);
        return true;
    }

    return false;
}

Qt::ItemFlags HostGroupListModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEditable | Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsUserCheckable;
}
