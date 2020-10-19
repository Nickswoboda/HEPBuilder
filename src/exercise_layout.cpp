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
    //get row/col of exercise
    int index = grid_->indexOf(&exercise);
    int row = 0, col = 0, r_span = 0, c_span = 0;
    grid_->getItemPosition(index, &row, &col, &r_span, &c_span);

    grid_->removeWidget(&exercise);

    //shift all exercises over by 1
    for (int i = index; i < grid_->count(); ++i){

        //use index instead of i because index seems to be based off of when it was added
        //not the position within the grid.
        Exercise* widget = static_cast<Exercise*>(grid_->itemAt(index)->widget());
        grid_->removeWidget(widget);
        grid_->addWidget(widget, row, col);

        ++col;
        if (col == grid_->columnCount()){
            col = 1;
            ++row;
        }
    }

    //update so the next exercise added is placed correctly
    --curr_col_;
    if (curr_col_ == 0){
        //columnCount returns 1 more than actual
        curr_col_ = grid_->columnCount() - 1;
        if (curr_row_ > 1){
            --curr_row_;
        }
    }

    exercises_.remove(exercise.name_);
}

void ExerciseLayout::RemoveAllItemsFromGrid()
{
    for (int i = 0; i < grid_->count(); ++i){
        grid_->removeWidget(grid_->itemAt(i)->widget());
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
    RemoveExerciseFromGrid(exercise);
    exercise.DeleteFromJson();
    //remove and hide exercise instead of deleting.
    //exercise will be deleted once mainwindow closes
    exercise.hide();

}
