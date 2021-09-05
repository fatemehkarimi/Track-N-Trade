#ifndef NETWORK_MANAGER_H
#define NETWORK_MANAGER_H

#include <QtWidgets>
#include <QtNetwork>
#include <QStack>

class NetworkManager : public QObject
{
    Q_OBJECT
public:
    NetworkManager();
    void fetchJson(QString url);

private slots:
    void finished();

private:
    QNetworkAccessManager* _network;
    QNetworkReply* pendingReply;
    QStack <QMetaObject::Connection> pendingConnections;
};

#endif