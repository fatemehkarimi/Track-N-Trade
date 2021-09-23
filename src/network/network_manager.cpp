#include <QNetworkReply>
#include <network/network_manager.h>

NetworkManager* NetworkManager::getInstance() {
    static NetworkManager networkManager;
    return &networkManager;
}


NetworkManager::NetworkManager() {
    this->_network = new QNetworkAccessManager();
    QObject::connect(
        _network, &QNetworkAccessManager::finished,
        this, [=](QNetworkReply* reply){
            QByteArray response = reply->readAll();
            QJsonDocument doc = QJsonDocument::fromJson(response);
            QJsonObject json = doc.object();
            emit jsonReady(reply->url().toString(), json);
            reply->deleteLater();
        });
}

void NetworkManager::fetchJson(QString url) {
    QNetworkRequest request(QUrl{url});
    _network->get(request);
}
