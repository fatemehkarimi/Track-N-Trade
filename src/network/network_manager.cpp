#include <QNetworkReply>
#include <network/network_manager.h>

NetworkManager::NetworkManager() {
    this->_network = new QNetworkAccessManager();
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
    emit jsonReady(json);

    QMetaObject::Connection c = pendingConnections.pop();
    QObject::disconnect(c);
    pendingReply->deleteLater();
}