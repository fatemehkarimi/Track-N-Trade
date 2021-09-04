#ifndef COIN_H
#define COIN_H

#include <QString>
#include <QPixmap>

class Coin
{
public:
    Coin(QString name, QString symbol, QString logo_path);
    QString name();
    QString symbol();
    QPixmap logo();

private:
    QString _name;
    QString _symbol;
    QPixmap _logo;
};

#endif