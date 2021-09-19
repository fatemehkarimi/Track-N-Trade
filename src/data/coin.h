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
    void setPrice(double price);
    double getPrice();

private:
    QString _name;
    QString _symbol;
    double price; /* price depends on selected exchange by user */
    bool _fiat;
    QPixmap _logo;
};

#endif