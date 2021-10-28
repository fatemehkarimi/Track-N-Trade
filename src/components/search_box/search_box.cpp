#include "search_box.h"

SearchBox::SearchBox(QString objectName, QWidget* parent)
    : QFrame(parent)
{
    setObjectName(objectName);
    
    layout = new QHBoxLayout(this);
    layout->setMargin(0);

    QLineEdit* input = new QLineEdit();
    input->setPlaceholderText("Search");

    QPixmap icon(":/icons/searchIcon");
    QLabel* iconLabel = new QLabel();
    iconLabel->setPixmap(icon);

    layout->addWidget(iconLabel);
    layout->addWidget(input);
}