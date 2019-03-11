#ifndef HOSTSLISTITEM_H
#define HOSTSLISTITEM_H

#include <QString>
#include <QVariant>
#include <QDateTime>

class HostsListItem
{
public:
    enum Field {
        Name = 0,
        Hosts,
        Description,
        Added,
        IsActive,
        IsCommon
    };

    HostsListItem();
    HostsListItem(QString name, QString description, QString hosts, bool isActive);

    QString name;
    QString hosts;
    QString description;
    QDateTime added;
    bool isActive;
    bool isCommon;

    QVariant data(int column);
    bool setData(int column, const QVariant &value, int role);
};

#endif // HOSTSLISTITEM_H
