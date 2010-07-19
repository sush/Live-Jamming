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
    void    channelsListed(QList<std::string>);
};

#endif // CHANNELSEARCH_H
