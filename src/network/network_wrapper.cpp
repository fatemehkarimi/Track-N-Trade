#include "network_wrapper.h"

NetworkWrapper::NetworkWrapper() {
    networkManager = NetworkManager::getInstance();
    QObject::connect(networkManager, &NetworkManager::jsonReady,
        this, &NetworkWrapper::handleResponseReady);
}

NetworkWrapper::~NetworkWrapper() {
    QObject::disconnect(this);
}

void NetworkWrapper::fetchJson(QString url) {
    networkManager->fetchJson(url);
}

void NetworkWrapper::registerObserver(QString url, NetworkObserver* observer) {

}

void NetworkWrapper::removeObserver(QString url, NetworkObserver* observer) {

}

void NetworkWrapper::handleResponseReady(QString url, QJsonObject json) {

}