#include "routine_layout.h"

RoutineLayout::RoutineLayout(QWidget *parent) : QWidget(parent)
{
    h_box_ = new QHBoxLayout(this);
    setLayout(h_box_);
}

void RoutineLayout::AddExercise(Exercise& exercise){
   h_box_->addWidget(&exercise);
   exercise.add_button_->setText("-");
}
