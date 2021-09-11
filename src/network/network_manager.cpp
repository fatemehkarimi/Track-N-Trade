#include <QNetworkReply>
#include <network/network_manager.h>

NetworkManager::NetworkManager() {
    this->_network = new QNetworkAccessManager();
}

void NetworkManager::fetchJson(QString url) {
    QNetworkRequest request(QUrl{url});
    QNetworkReply* reply = _network->get(request);
    QMetaObject::Connection c1 = QObject::connect(
        reply, &QNetworkReply::finished,
        this, [=](){
            QByteArray response = reply->readAll();
            QJsonDocument doc = QJsonDocument::fromJson(response);
            QJsonObject json = doc.object();
            emit jsonReady(json);
            reply->deleteLater();
        });
}
