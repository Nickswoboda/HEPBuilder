#include "exercise_card.h"

ExerciseCard::ExerciseCard(const Exercise& exercise, QWidget *parent) : QWidget(parent)
{
    ui_.setupUi(this);

    ui_.image->setScaledContents(true);
    ui_.image->setPixmap(*(exercise.pixmap()));

    ui_.name_label->setText(exercise.name_);
    ui_.instruction_label->setText(exercise.instruction_);

    ui_.text_layout->setAlignment(Qt::AlignTop);

}
