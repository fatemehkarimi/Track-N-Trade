#include "exchange_composite.h"
#include "exchange_leaf.h"


CompositeExchange::CompositeExchange(Routes* api_routes) {
    routes = api_routes;
    networkManager = new NetworkManager();
    getExchangeList();
}

QString CompositeExchange::getName() {
    return nullptr;
}

QString CompositeExchange::getSymbol() {
    return nullptr;
}

void CompositeExchange::getCoin(QString symbol) {

}

void CompositeExchange::getCoinList() {

}

void CompositeExchange::getExchange(QString exchange_symbol) {

}

void CompositeExchange::getExchangeList() {
    if(exchangeList.size() > 0) {
        emit exchangeListReady(exchangeList);
        return;
    }
    bool connected = QObject::connect(
        networkManager, &NetworkManager::jsonReady,
        this, &CompositeExchange::getExchangeListJson,
        Qt::UniqueConnection);
    if(connected)
        networkManager->fetchJson(routes->getExchangeListPath());
}

void CompositeExchange::getExchangeListJson(QJsonObject json) {
    QObject::disconnect(networkManager, &NetworkManager::jsonReady,
                        this, &CompositeExchange::getExchangeListJson);

    QJsonArray exchange_array = json["result"].toArray();
    foreach (const QJsonValue& value, exchange_array) {
        QJsonObject obj = value.toObject();
        QString symbol = obj["symbol"].toString();
        QString name = obj["name"].toString();
        QString route = obj["route"].toString();
        bool active = obj["active"].toBool();

        if(!active)
            continue;

        LeafExchange* exchange = new LeafExchange(routes, name, symbol);
        exchangeList[name] = exchange;
    }
    emit exchangeListReady(exchangeList);
}