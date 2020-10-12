#include "exercise_layout.h"

ExerciseLayout::ExerciseLayout(QWidget* parent)
    :QWidget(parent)
{
    grid_ = new QGridLayout(this);
    grid_->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    setLayout(grid_);
}

void ExerciseLayout::AddExercise(Exercise& exercise){
    grid_->addWidget(&exercise, curr_row_, curr_col_);
    exercise.add_button_->setText("+");

    if (curr_col_ == max_cols_){
       ++curr_row_;
       curr_col_ = 1;
    }
    else{
        ++curr_col_;
    }
}

Exercise* ExerciseLayout::GetExerciseByName(const QString& name)
{
    for (int i = 0; i < grid_->count(); ++i){
        //TODO: implement hashmap for quicker lookup
        Exercise* ex = dynamic_cast<Exercise*>(grid_->itemAt(i)->widget());

        if (ex && ex->name_ == name){
            return ex;
        }
    }

    return nullptr;
}
