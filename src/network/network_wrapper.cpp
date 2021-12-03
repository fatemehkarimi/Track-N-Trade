#include "network_wrapper.h"

NetworkWrapper::NetworkWrapper() {
    networkManager = NetworkManager::getInstance();
    QObject::connect(networkManager, &NetworkManager::jsonReady,
        this, &NetworkWrapper::handleResponseReady);
}

NetworkWrapper::~NetworkWrapper() {
    QObject::disconnect(this);
}

void NetworkWrapper::fetchJson(QString url, std::shared_ptr <NetworkObserver> o) {
    networkManager->fetchJson(url);
    registerObserver(url, o);
}

void NetworkWrapper::registerObserver(QString url, std::shared_ptr <NetworkObserver> o) {
    observerPool.registerObserver(url, o);
}

void NetworkWrapper::handleResponseReady(QString url, QJsonObject json) {
    auto iterator = observerPool.createIterator(url);

    while(iterator.hasNext()) {
        std::shared_ptr <NetworkObserver> o = iterator.next();
        o->handleJsonResponse(url, json);
    }
    observerPool.removeObservers(url);
}