#include "api_cryptowatch.h"

CryptowatchApi::CryptowatchApi() {
    network_manager = new NetworkManager(this);
    getExchangeList();
}

void CryptowatchApi::getExchangeList() {
    network_manager->fetchJson(api_config.getExchangeListPath());
    QMetaObject::Connection c = QObject::connect(
        this, &CryptowatchApi::jsonReady, this, &CryptowatchApi::exchangeListReady);

    connection_list.push(c);
}

void CryptowatchApi::exchangeListReady(QJsonObject json) {
    while(!connection_list.isEmpty()) {
        QMetaObject::Connection c = connection_list.pop();
        QObject::disconnect(c);
    }

    qDebug() << QJsonDocument(json).toJson(QJsonDocument::Compact);
}

Exchange CryptowatchApi::currentExchange() {

}

QList <Exchange> CryptowatchApi::exchangeList() {
    return exchange_list;
}

void CryptowatchApi::setExchangeByName(QString name) {

}

