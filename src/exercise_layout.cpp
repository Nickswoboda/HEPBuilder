#include "exercise_layout.h"

ExerciseLayout::ExerciseLayout(QWidget* parent)
    :QWidget(parent)
{
    grid_ = new QGridLayout(this);
    setLayout(grid_);
}

void ExerciseLayout::AddExercise(QWidget *exercise){
    grid_->addWidget(exercise, curr_row_, curr_col_);

    ++curr_col_;
    if (curr_col_ > max_cols_){
       ++curr_row_;
       curr_col_ = 0;
    }

}
