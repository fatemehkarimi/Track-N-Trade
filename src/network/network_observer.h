#ifndef NETWORK_OBSERVER_H
#define NETWORK_OBSERVER_H

#include <QtWidgets>

class NetworkObserver {
public:
    virtual void handleJsonResponse(QString url, QJsonObject json) = 0;
};

#endif