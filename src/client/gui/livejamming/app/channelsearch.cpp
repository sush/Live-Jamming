#include "channelsearch.h"
#include <proxy.h>

#include <string>
#include <Component_Channel.h> // to remove
#include <Component_Session.h>

#include <qdebug.h>

ChannelSearch::ChannelSearch(Proxy *proxy, QWidget *parent)
{
    setupUi(this);
    proxy->channel()->Send_List(proxy->session()->_session);
    connect(proxy, SIGNAL(channelsListed(QStringList)), this, SLOT(channelsListed(QStringList)));
    show();
}

void    ChannelSearch::channelsListed(QStringList channelNameList)
{
    foreach(QString channelName, channelNameList)
        channelTree->addTopLevelItem(new QTreeWidgetItem(QStringList(channelName)));
}
