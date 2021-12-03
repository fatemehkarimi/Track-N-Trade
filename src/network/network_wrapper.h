#ifndef NETWORK_WRAPPER_H
#define NETWORK_WRAPPER_H

#include "network_manager.h"
#include "network_observer.h"
#include "observer_pool.h"

class NetworkWrapper : public QObject {
    Q_OBJECT
public:
    explicit NetworkWrapper();
    ~NetworkWrapper();
    void fetchJson(QString url);

    void registerObserver(QString url, NetworkObserver* observer);
    void removeObserver(QString url, NetworkObserver* observer);

public slots:
    void handleResponseReady(QString url, QJsonObject json);

private:
    NetworkManager* networkManager;
    ObserverPool <NetworkObserver> observerPool;
};

#endif