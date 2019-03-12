#ifndef HOSTSLISTMODEL_H
#define HOSTSLISTMODEL_H

#include <QAbstractTableModel>
#include <QVector>
#include <QSize>
#include <QFile>
#include <QRegularExpression>
#include <QDateTime>
#include <QIcon>
#include <QString>

#include "hostslistitem.h"

class HostsListModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit HostsListModel(QObject *parent = nullptr);

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // Editable:
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;

    bool removeTemplateItem(QModelIndex &index);
    bool addTemplateItem(HostsListItem *item);

    QModelIndex moveTemplateItem(QModelIndex &index, bool isMoveUp);

    Qt::ItemFlags flags(const QModelIndex& index) const override;

    void parse();
    bool save();

private:
    QVector<HostsListItem*> *hostItems;
};

#endif // HOSTSLISTMODEL_H
