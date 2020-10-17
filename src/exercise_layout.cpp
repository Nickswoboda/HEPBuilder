#include "exercise_layout.h"

ExerciseLayout::ExerciseLayout(QWidget* parent)
    :QWidget(parent)
{
    grid_ = new QGridLayout(this);
    grid_->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    setLayout(grid_);
}

void ExerciseLayout::AddExercise(Exercise& exercise){
    exercises_[exercise.name_] = &exercise;
    AddExerciseToGrid(exercise);
}

void ExerciseLayout::AddExerciseToGrid(Exercise &exercise)
{
    exercise.add_button_->setText("+");
    grid_->addWidget(&exercise, curr_row_, curr_col_);
    if (curr_col_ == max_cols_){
       ++curr_row_;
       curr_col_ = 1;
    }
    else{
        ++curr_col_;
    }
}
void ExerciseLayout::RemoveExerciseFromGrid(Exercise &exercise)
{
    //TODO: this seems inefficient, find a better way
    RemoveAllItemsFromGrid();
    for (auto& ex : exercises_){
        if (ex != &exercise){
            AddExerciseToGrid(*ex);
        }
    }
    exercises_.remove(exercise.name_);
}

void ExerciseLayout::RemoveAllItemsFromGrid()
{
    for (int i = 0; i < grid_->count(); ++i){
        grid_->removeItem(grid_->itemAt(i));
    }
    curr_row_ = 1;
    curr_col_ = 1;
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
    //Need to remove all items then place them back in if they fit criteria
    //if not there will be a gap between exercises where the hidden ones were
    RemoveAllItemsFromGrid();
    for (auto& ex : exercises_){
        if (ex->name_.contains(name, Qt::CaseInsensitive)){
            ex->show();
            AddExerciseToGrid(*ex);
        }
        else{
            ex->hide();
        }
    }

}

void ExerciseLayout::SearchByTags(const QSet<QString>& tags)
{
    RemoveAllItemsFromGrid();
    for (auto& ex : exercises_){
        if (ex->HasTags(tags)){
            ex->show();
            AddExerciseToGrid(*ex);
        }
        else{
            ex->hide();
        }
    }
}

void ExerciseLayout::DeleteExercise(Exercise& exercise)
{
    exercises_.remove(exercise.name_);
    exercise.DeleteFromJson();
    //remove and hide exercise instead of deleting.
    //exercise will be deleted once mainwindow closes
    grid_->removeWidget(&exercise);
    exercise.hide();

}
