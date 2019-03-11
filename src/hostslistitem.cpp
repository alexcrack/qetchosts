#include "hostslistitem.h"

HostsListItem::HostsListItem():
    isActive(true), isCommon(false)
{

}

HostsListItem::HostsListItem(QString name, QString description, QString hosts, bool isActive):
    name(name), hosts(hosts), description(description), isActive(isActive)
{}

QVariant HostsListItem::data(int column)
{
    switch(column) {
    case Field::Name: return this->name;
    case Field::Hosts: return this->hosts;
    case Field::Added: return this->added;
    case Field::Description: return this->description;
    case Field::IsActive: return this->isActive;
    default: return QVariant();
    }
}

bool HostsListItem::setData(int column, const QVariant &value, int role)
{
    if (role == Qt::EditRole) {
        switch (column) {
        case Field::Name:
            name = value.toString();
            break;
        case Field::Hosts:
            hosts = value.toString();
            break;
        }
    }

    if (role == Qt::CheckStateRole) {
        isActive = value == Qt::Checked;
    }

    return true;
}
