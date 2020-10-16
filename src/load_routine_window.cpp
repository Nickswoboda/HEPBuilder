#include "load_routine_window.h"
#include "ui_loadroutinewindow.h"

#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>

LoadRoutineWindow::LoadRoutineWindow(ExerciseLayout& exercise_layout, RoutineLayout& routine_layout, QWidget *parent) :
    QDialog(parent), ui_(new Ui::LoadRoutineWindow), exercise_layout_(exercise_layout), routine_layout_(routine_layout)
{
    ui_->setupUi(this);

    LoadRoutineNames();

    connect(ui_->load_button, SIGNAL(clicked()), this, SLOT(OnLoadButtonPressed()));
}

LoadRoutineWindow::~LoadRoutineWindow()
{
    delete ui_;
}

void LoadRoutineWindow::LoadRoutineNames()
{
    QFile file("assets/routines.json");

    if (!file.open(QIODevice::ReadOnly)){
        return;
    }

    QByteArray data = file.readAll();
    QJsonDocument doc(QJsonDocument::fromJson(data));
    json_obj_ = doc.object();

    for (auto& key : json_obj_.keys()){
        ui_->routine_list->addItem(key);
    }

    file.close();
}

void LoadRoutineWindow::OnLoadButtonPressed()
{
    routine_layout_.Clear();

    auto selection = ui_->routine_list->selectedItems();
    QString name = selection[0]->text();
    QJsonArray routine = json_obj_[name].toArray();

    for (auto item : routine){
        Exercise* ex = exercise_layout_.GetExerciseByName(item.toString());
        if (ex){
            routine_layout_.AddExercise(*ex);
            exercise_layout_.RemoveExerciseFromGrid(*ex);
        }

    }
}

void LoadRoutineWindow::OnCancelButtonPressed()
{

}

void LoadRoutineWindow::OnDeleteButtonPressed()
{

}
