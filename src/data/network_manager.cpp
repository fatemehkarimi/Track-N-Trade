#include <QNetworkReply>
#include "network_manager.h"

NetworkManager::NetworkManager(JsonReceiver* receiver) {
    this->_network = new QNetworkAccessManager();
    this->receiver = receiver;
}

void NetworkManager::fetchJson(QString url) {
    QNetworkRequest request(QUrl{url});
    pendingReply = _network->get(request);

    QMetaObject::Connection c1 = QObject::connect(
        pendingReply, &QNetworkReply::finished,
        this, &NetworkManager::finished);
    
    pendingConnections.push(c1);
}

void NetworkManager::finished() {
    QByteArray response = pendingReply->readAll();
    QJsonDocument doc = QJsonDocument::fromJson(response);
    QJsonObject json = doc.object();
    receiver->jsonReady(json);

    QMetaObject::Connection c = pendingConnections.pop();
    QObject::disconnect(c);
    pendingReply->deleteLater();
}