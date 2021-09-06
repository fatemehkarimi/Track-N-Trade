#ifndef JSON_RECEIVER_H
#define JSON_RECEIVER_H

#include <QtWidgets>

class JsonReceiver : public QObject
{
    Q_OBJECT
signals:
    void jsonReady(QJsonObject);
};

#endif