#ifndef NETWORK_MANAGER_H
#define NETWORK_MANAGER_H

#include <QtWidgets>
#include <QtNetwork>
#include <QStack>

class NetworkManager : public QObject
{
    Q_OBJECT
public:
    static NetworkManager* getInstance();
    void fetchJson(QString url);

signals:
    void jsonReady(QString url, QJsonObject);

private:
    NetworkManager();
    QNetworkAccessManager* _network;
};

#endif