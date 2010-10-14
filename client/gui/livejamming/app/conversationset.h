#ifndef CONVERSATIONSET_H
#define CONVERSATIONSET_H

#include <QWidget>
#include <ui_conversationset.h>

#include <qdebug.h>

class ConversationSet : public QWidget, private Ui::ConversationSet
{
Q_OBJECT
public:
    explicit ConversationSet(QWidget *parent = 0);

signals:
    void    msgSend(const QString&);

public slots:
    void    addMessage(const QString& client, const QString& msg);
    void    addEvent(const QString& event);

private slots:
    void    sendMsg();
};

#endif // CONVERSATIONSET_H
