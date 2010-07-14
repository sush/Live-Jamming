#ifndef CHANNELLIST_H
#define CHANNELLIST_H

#include <QTreeWidget>

class QModelIndex;
class QTreeWidgetItem;

class ChannelList : public QTreeWidget
{
Q_OBJECT
public:
    explicit ChannelList(QWidget *parent = 0);
    QTreeWidgetItem*    itemFromIndex(const QModelIndex&);

signals:

public slots:

};

#endif // CHANNELLIST_H
