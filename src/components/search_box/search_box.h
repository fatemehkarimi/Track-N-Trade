#ifndef SEARCH_BOX_H
#define SEARCH_BOX_H

#include <QWidget>
#include <QtWidgets>

class SearchBox : public QFrame
{
    Q_OBJECT
public:
    SearchBox(QString objectName, QWidget* parent=nullptr);

private:
    QHBoxLayout* layout;
};

#endif
