#ifndef NETWORK_MANAGER_H
#define NETWORK_MANAGER_H

#include <QtWidgets>
#include <QtNetwork>
#include <QStack>

#include "json_receiver.h"

class NetworkManager : public QObject
{
    Q_OBJECT
public:
    NetworkManager(JsonReceiver* receiver);
    void fetchJson(QString url);

private slots:
    void finished();

private:
    JsonReceiver* receiver;
    QNetworkAccessManager* _network;
    QNetworkReply* pendingReply;
    QStack <QMetaObject::Connection> pendingConnections;
};

#endif