#include "api_cryptowatch.h"

CryptowatchApi::CryptowatchApi() {
    network_manager = new NetworkManager(this);
    getExchangeList();
}

void CryptowatchApi::getExchangeList() {
    network_manager->fetchJson(api_config.getExchangeListPath());
    QMetaObject::Connection c = QObject::connect(
        this, &CryptowatchApi::jsonReady,
        this, &CryptowatchApi::exchangeListReady);

    connection_list.push(c);
}

void CryptowatchApi::exchangeListReady(QJsonObject json) {
    while(!connection_list.isEmpty()) {
        QMetaObject::Connection c = connection_list.pop();
        QObject::disconnect(c);
    }

    QJsonArray exchange_array = json["result"].toArray();
    foreach (const QJsonValue& value, exchange_array) {
        QJsonObject obj = value.toObject();
        QString symbol = obj["symbol"].toString();
        QString name = obj["name"].toString();
        QString route = obj["route"].toString();
        bool active = obj["active"].toBool();

        if(active) {
            Exchange e(name, symbol);
            exchange_list[symbol] = e;
        }
    }
}

Exchange CryptowatchApi::getExchange(QString exchange_symbol) {

}

QMap <QString, Exchange> CryptowatchApi::exchangeList() {
    return exchange_list;
}
