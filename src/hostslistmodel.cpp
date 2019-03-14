#include "hostslistmodel.h"

#include <QDebug>

HostsListModel::HostsListModel(QObject *parent)
    : QAbstractTableModel(parent)
{
    parse();
}

int HostsListModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    hostItems->size();
}

int HostsListModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return 3;
}

QVariant HostsListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    int i = index.row();

    if (!index.isValid())
        return QVariant();

    if (role == Qt::DisplayRole) {
        return hostItems->at(i)->data(index.column());
    }

    if (role == Qt::SizeHintRole) {
        return QSize(24, 24);
    }

    if (role == Qt::DecorationRole) {
        return QIcon(":/items/icons/icons8-list-view-item-16.png");
    }

    if (role == Qt::EditRole) {
        return hostItems->at(i)->data(index.column());
    }

    if (role == Qt::ToolTipRole) {
        return hostItems->at(i)->data(HostsListItem::Field::Description);
    }

    if (role == Qt::StatusTipRole) {
        HostsListItem *item = hostItems->at(i);

        return QString("%1. Created at %2")
                .arg(item->description)
                .arg(item->added.toString());
    }

    if(role == Qt::CheckStateRole) {
        return hostItems->at(i)->isActive ? Qt::Checked : Qt::Unchecked;
    }

    return QVariant();
}

bool HostsListModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (data(index, role) != value) {
        HostsListItem *item = hostItems->at(index.row());

        bool changed = item->setData(index.column(), value, role);

        emit dataChanged(index, index, QVector<int>() << role);

        return changed;
    }

    return false;
}

bool HostsListModel::removeTemplateItem(QModelIndex &index)
{
    beginRemoveRows(index, index.row(), index.row());

    hostItems->remove(index.row());

    endRemoveRows();

    return true;
}

QModelIndex HostsListModel::addTemplateItem(HostsListItem *item)
{
    item->added = QDateTime::currentDateTime();

    beginInsertRows(QModelIndex(), 1, 1);

    hostItems->push_back(item);

    endInsertRows();

    QModelIndex index = this->index(hostItems->size() - 1, HostsListItem::Field::Name);

    return index;
}

QModelIndex HostsListModel::moveTemplateItem(QModelIndex &index, bool isMoveUp)
{
    int currentRow = index.row();
    int destinationRow = isMoveUp ? currentRow - 1 : currentRow + 1;

    if (destinationRow >= 0 && destinationRow < hostItems->size()) {
        beginMoveRows(index, currentRow, currentRow, index, isMoveUp ? destinationRow : destinationRow + 1);

        hostItems->move(currentRow, destinationRow);

        endMoveRows();

        return this->index(destinationRow, HostsListItem::Field::Name);
    }

    return index;
}

Qt::ItemFlags HostsListModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEditable | Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsUserCheckable;
}

void HostsListModel::parse()
{
    QFile hostsFile(HOSTS_FILEPATH);

    QRegularExpression rStart("^##### EtcHosts ## Section: (.+) ## Added: (\\d{4}-\\d{2}-\\d{2}T\\d{2}:\\d{2}:\\d{2}) ## Description: (.+) #####");
    QRegularExpression rEnd("^##### END #####");

    hostItems = new QVector<HostsListItem*>();
    HostsListItem *item = new HostsListItem();

    if (hostsFile.open(QIODevice::ReadOnly)) {
        QTextStream in(&hostsFile);

        item->name = "Common";
        item->description = "Common hosts";
        item->isCommon = true;

        while (!in.atEnd()) {
            QString line = in.readLine();

            QRegularExpressionMatch matchedStart = rStart.match(line);
            QRegularExpressionMatch matchedEnd = rEnd.match(line);

            if (matchedStart.hasMatch()) {
                // Common group is ended. Save it
                if (item->isCommon) {
                    hostItems->push_back(item);
                }

                // Start a new group
                item = new HostsListItem();

                item->name = matchedStart.captured(1);
                item->added = QDateTime::fromString(matchedStart.captured(2), Qt::ISODate);
                item->description = matchedStart.captured(3);
            } else if (matchedEnd.hasMatch()) {
                hostItems->push_back(item);
            } else {
                if (line.startsWith("#--")) {
                    line = line.remove(0, 3);

                    item->isActive = false;
                }

                item->hosts = item->hosts.append(line).append("\n");
            }
        }

        if (item->isCommon) {
            hostItems->push_back(item);
        }

        hostsFile.close();
    }
}

bool HostsListModel::save()
{
    QFile hostsFile(HOSTS_FILEPATH);

    if (hostsFile.open(QIODevice::WriteOnly)) {
        QTextStream out(&hostsFile);
        QVectorIterator<HostsListItem*> i(*hostItems);

        while (i.hasNext()) {
            HostsListItem *item = i.next();

            if (!item->isCommon) {
                out << QString("##### EtcHosts ## Section: %1 ## Added: %2 ## Description: %3 #####")
                       .arg(item->name)
                       .arg(item->added.toString(Qt::ISODate))
                       .arg(item->description)
                       .append("\n");
            }

            QStringList lines = item->hosts.split("\n");
            foreach (auto line, lines) {
                if (!item->isActive) {
                    out << "#--";
                }

                out << line << endl;
            }

            if (!item->isCommon) {
                out << "##### END #####" << endl;
            }
        }

        return true;
    }

    return false;
}
