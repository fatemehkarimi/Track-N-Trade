#ifndef COIN_H
#define COIN_H

#include <QString>
#include <QPixmap>

class Coin
{
public:
    Coin(QString name, QString symbol, bool _fiat, QString logo_path);
    QString name();
    QString symbol();
    QPixmap logo();

private:
    QString _name;
    QString _symbol;
    bool _fiat;
    QPixmap _logo;
};

#endif