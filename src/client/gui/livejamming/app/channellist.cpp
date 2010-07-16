#include "channellist.h"

ChannelList::ChannelList(QWidget *parent) :
    QTreeWidget(parent)
{
}

QTreeWidgetItem*    ChannelList::itemFromIndex(const QModelIndex & index)
{
    return QTreeWidget::itemFromIndex(index);
}
