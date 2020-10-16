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
    exercises_[exercise.name_] = &exercise;
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
    if (exercises_.contains(name)){
        return exercises_[name];
    }

    return nullptr;
}

void ExerciseLayout::SearchByName(const QString& name)
{
    for (auto& ex : exercises_){
        //show if was hidden by previous search
        ex->show();
        if (!ex->name_.toLower().contains(name.toLower())){
            ex->hide();
        }
    }

}

void ExerciseLayout::SearchByTags(const QSet<QString>& tags)
{
    for (auto& ex : exercises_){
        //show if was hidden by previous search
        ex->show();
        for (const auto& tag : tags){
            if (!ex->tags_.contains(tag)){
                ex->hide();
                break;
            }
        }
    }
}
