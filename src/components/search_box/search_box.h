#ifndef SEARCH_BOX_H
#define SEARCH_BOX_H

#include <QWidget>
#include <QtWidgets>

class SearchBox : public QWidget
{
    Q_OBJECT
public:
    SearchBox(QWidget* parent=nullptr);

private:
    QHBoxLayout* layout;
};

#endif
