#include <QNetworkReply>
#include <network/network_manager.h>

NetworkManager* NetworkManager::getInstance() {
    static NetworkManager networkManager;
    return &networkManager;
}


NetworkManager::NetworkManager() {
    this->_network = new QNetworkAccessManager();
}

void NetworkManager::fetchJson(QString url) {
    QNetworkRequest request(QUrl{url});
    QNetworkReply* reply = _network->get(request);

    auto conn = std::make_shared<QMetaObject::Connection>();
    *conn = QObject::connect(
        reply, &QNetworkReply::finished,
        this, [=](){
            QObject::disconnect(*conn);
            QByteArray response = reply->readAll();
            QJsonDocument doc = QJsonDocument::fromJson(response);
            QJsonObject json = doc.object();
            emit jsonReady(reply->url().toString(), json);
            reply->deleteLater();
        });
}
