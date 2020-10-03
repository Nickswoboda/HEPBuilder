#include "tooltip.h"

#include <QVBoxLayout>
#include <QLabel>

Tooltip::Tooltip(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout* layout = new QVBoxLayout(this);
    setLayout(layout);

    QLabel* name = new QLabel("name");
    layout->addWidget(name);


}
