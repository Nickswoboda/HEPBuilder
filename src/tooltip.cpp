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
    name_label_->setFixedSize(165, 30);

    instruction_label_ = new QLabel("Instruction");
    instruction_label_->setWordWrap(true);
    instruction_label_->setStyleSheet("border-bottom: 0px");
    instruction_label_->setFixedSize(165, 125);
    instruction_label_->setAlignment(Qt::AlignTop);

    layout->addWidget(name_label_);
	layout->addWidget(instruction_label_);

    setFixedSize(165, 160);
    hide();
}

void Tooltip::PlaceOnExercise(const Exercise& ex)
{
   QWidget* main_window = parentWidget();
   QPoint mouse_pos = main_window->mapFromGlobal(QCursor::pos());
   QPoint mouse_pos_on_ex = ex.mapFromGlobal(QCursor::pos());

   //make sure tooltip is placed below the exercise that is being hovered
   mouse_pos.rx() -= mouse_pos_on_ex.x();
   mouse_pos.ry() += ex.geometry().height() - mouse_pos_on_ex.y();

   //make sure tooltip is placed completely within the main window
   if (mouse_pos.x() + geometry().width() > main_window->geometry().width()){
       mouse_pos.rx() = main_window->geometry().width() - geometry().width();
   }
   if (mouse_pos.y() + geometry().height() > main_window->geometry().height()){
       mouse_pos.ry() = main_window->geometry().height() - geometry().height();
   }
   move(mouse_pos.x(), mouse_pos.y());
   name_label_->setText(ex.name_);
   instruction_label_->setText(ex.instruction_);
   show();
}
