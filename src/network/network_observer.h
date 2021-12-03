#ifndef NETWORK_OBSERVER_H
#define NETWORK_OBSERVER_H

#include <QtWidgets>

class NetworkObserver {
    virtual void receiveJson(QString url, QJsonObject json) = 0;
};

#endif