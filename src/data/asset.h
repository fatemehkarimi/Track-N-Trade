#ifndef ASSET_H
#define ASSET_H

#include <QString>
#include <QPixmap>
#include "api_item.h"

class Asset : public APIItem
{
public:
    Asset(QString id, QString name, QString symbol, bool fiat, QString logo_path);
    QString getId() override;
    QString getSymbol() override;
    QString getName();
    QPixmap getLogo();

private:
    QString id;
    QString name;
    QString symbol;
    bool fiat;
    QPixmap logo;
};

#endif