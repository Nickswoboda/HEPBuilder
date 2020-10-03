#include "tooltip.h"

#include <QVBoxLayout>
#include <QLabel>

Tooltip::Tooltip(QWidget *parent) : QWidget(parent)
{
	setStyleSheet("background: aliceblue; border: 1px solid black");
    setAttribute(Qt::WA_TransparentForMouseEvents);

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->setAlignment(Qt::AlignTop);
    layout->setMargin(0);
    layout->setSpacing(0);
    setLayout(layout);

    name_label_ = new QLabel("Name");
    name_label_->setWordWrap(true);
    name_label_->setStyleSheet("background: #B0C4DE; font-weight: bold");

    instruction_label_ = new QLabel("Instruction");
    instruction_label_->setWordWrap(true);

    layout->addWidget(name_label_);
	layout->addWidget(instruction_label_);
}
