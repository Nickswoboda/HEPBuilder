#include "exercise_card.h"

ExerciseCard::ExerciseCard(const Exercise& exercise, QWidget *parent) : QWidget(parent)
{
    ui_.setupUi(this);


    ui_.image->setScaledContents(true);
    ui_.image->setPixmap(*(exercise.pixmap()));

    ui_.text->setText(exercise.name_ + "\n\n" + exercise.instruction_);
}
