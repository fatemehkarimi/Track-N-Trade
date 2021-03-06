#include "network_wrapper.h"

NetworkWrapper::NetworkWrapper() {
    networkManager = NetworkManager::getInstance();
    QObject::connect(networkManager, &NetworkManager::jsonReady,
        this, &NetworkWrapper::handleResponseReady);
}

NetworkWrapper::~NetworkWrapper() {
    QObject::disconnect(this);
    observerPool.removeAll();
}

void NetworkWrapper::fetchJson(QString url, NetworkObserver* o) {
    networkManager->fetchJson(url);
    registerObserver(url, o);
}

void NetworkWrapper::registerObserver(QString url, NetworkObserver* o) {
    observerPool.registerObserver(url, o);
}

void NetworkWrapper::handleResponseReady(QString url, QJsonObject json) {
    auto iterator = observerPool.createIterator(url);

    while(iterator.hasNext()) {
        NetworkObserver* o = iterator.next();
        o->handleJsonResponse(url, json);
    }
    observerPool.removeObservers(url);
}