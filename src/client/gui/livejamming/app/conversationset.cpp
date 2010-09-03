
#include "conversationset.h"

ConversationSet::ConversationSet(QWidget *parent) :
    QWidget(parent)
{
    setupUi(this);

    input->setFocus(Qt::OtherFocusReason);

    //connect(input, SIGNAL(returnPressed()), this, SLOT(sendMsg()));
    connect(send, SIGNAL(pressed()), this, SLOT(sendMsg()));
}

void    ConversationSet::addMessage(const QString &client, const QString &msg)
{
    display->append("<strong>" + client + "</strong>: " + msg + "\n");
    display->ensureCursorVisible();
}

void    ConversationSet::addEvent(const QString &event)
{
    display->append("* <i>" + event + "</i>");
}

void    ConversationSet::sendMsg()
{
    emit msgSend(input->text());
    input->clear();
}

