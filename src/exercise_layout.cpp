#include "exercise_layout.h"

ExerciseLayout::ExerciseLayout(QWidget* parent)
    :QWidget(parent)
{
    grid_ = new QGridLayout(this);
    grid_->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    grid_->setSpacing(16);
    setLayout(grid_);
}

void ExerciseLayout::AddExercise(Exercise& exercise){
    exercises_[exercise.name_] = &exercise;
    AddExerciseToGrid(exercise);
    exercise.add_button_->setText("+");
    exercise.edit_button_->show();
}

void ExerciseLayout::AddExerciseToGrid(Exercise &exercise)
{
    int count = grid_->count();
    if (count == 0){
        grid_->addWidget(&exercise, 0,0);
    }
    else{
        //get row/col of last exercise
        int row = 0, col = 0, r_span = 0, c_span = 0;
        grid_->getItemPosition(grid_->count() - 1, &row, &col, &r_span, &c_span);

        ++col;
        if (col == max_cols_){
            ++row;
            col = 0;
        }


        grid_->addWidget(&exercise, row, col);
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
            col = 0;
            ++row;
        }
    }

    exercises_.remove(exercise.name_);
}

void ExerciseLayout::RemoveAllItemsFromGrid()
{
    while(!grid_->isEmpty()){
        auto exercise = grid_->itemAt(0)->widget();
        exercise->hide();
        grid_->removeWidget(exercise);
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
    RemoveAllItemsFromGrid();
    for (auto& ex : exercises_){
        if (ex->name_.contains(name, Qt::CaseInsensitive)){
            AddExerciseToGrid(*ex);
            ex->show();
        }
    }

}

void ExerciseLayout::SearchByTags(const QSet<QString>& tags)
{
    RemoveAllItemsFromGrid();
    for (auto& ex : exercises_){
        if (ex->HasTags(tags)){
            AddExerciseToGrid(*ex);
            ex->show();
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
