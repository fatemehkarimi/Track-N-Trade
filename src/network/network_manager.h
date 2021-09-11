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

signals:
    void jsonReady(QJsonObject);

private:
    QNetworkAccessManager* _network;
};

#endif