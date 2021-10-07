#ifndef ASSET_H
#define ASSET_H

#include <QString>
#include <QPixmap>

class Asset
{
public:
    Asset(int id, QString name, QString symbol, bool _fiat, QString logo_path);
    int getId();
    QString getName();
    QString getSymbol();
    QPixmap getLogo();

private:
    int _id;
    QString _name;
    QString _symbol;
    bool _fiat;
    QPixmap _logo;
};

#endif