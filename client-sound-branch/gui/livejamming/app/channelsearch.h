#ifndef CHANNELSEARCH_H
#define CHANNELSEARCH_H

#include "ui_chanlist.h"
#include <QDialog>

class Proxy;

class ChannelSearch : public QDialog, private Ui::ChannelSearch
{
    Q_OBJECT
public:
    ChannelSearch(Proxy* proxy, QWidget* parent = 0);

public slots:
    void    channelsListed(QStringList);
    void    on_channelTree_doubleClicked(QModelIndex index);

signals:
    void    join(QString);

private:
    Proxy*  _proxy;
};

#endif // CHANNELSEARCH_H
