#include "channelsearch.h"
#include <proxy.h>

#include <string>
#include <Component_Channel.h> // to remove
#include <Component_Session.h>

#include <qdebug.h>

ChannelSearch::ChannelSearch(Proxy *proxy, QWidget *parent)
{
    proxy->channel()->Send_List(proxy->session()->_session);
    connect(proxy, SIGNAL(channelsListed(QList<std::string>)), this, SLOT(channelsListed(QList<std::string>)));
}

void    ChannelSearch::channelsListed(QList<std::string> channelNameList)
{
    foreach(std::string channelName, channelNameList)
        //QString::fromStdString(channelName);
        channelTree->addTopLevelItem(new QTreeWidgetItem(QStringList(QString::fromStdString(channelName))));
}
