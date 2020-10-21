#include "load_routine_window.h"
#include "ui_loadroutinewindow.h"

#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QMessageBox>

LoadRoutineWindow::LoadRoutineWindow(ExerciseLayout& exercise_layout, RoutineLayout& routine_layout, QWidget *parent) :
    QDialog(parent), ui_(new Ui::LoadRoutineWindow), exercise_layout_(exercise_layout), routine_layout_(routine_layout)
{
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    ui_->setupUi(this);

    LoadRoutineNames();

    connect(ui_->load_button, SIGNAL(clicked()), this, SLOT(OnLoadButtonPressed()));
    connect(ui_->cancel_button, SIGNAL(clicked()), this, SLOT(OnCancelButtonPressed()));
    connect(ui_->delete_button, SIGNAL(clicked()), this, SLOT(OnDeleteButtonPressed()));
}

LoadRoutineWindow::~LoadRoutineWindow()
{
    delete ui_;
}

void LoadRoutineWindow::LoadRoutineNames()
{
    QFile file("assets/routines.json");

    if (!file.open(QIODevice::ReadOnly)){
        QMessageBox::warning(this, "Unable to open file", "Could not load routines from routines.json file.");
        return;
    }

    QByteArray data = file.readAll();
    QJsonDocument doc(QJsonDocument::fromJson(data));
    json_obj_ = doc.object();

    for (auto& key : json_obj_.keys()){
        ui_->routine_list->addItem(key);
    }
}

void LoadRoutineWindow::OnLoadButtonPressed()
{
    auto selection = ui_->routine_list->selectedItems();
    if (selection.empty()) return;

    QString name = selection[0]->text();
    QJsonArray routine = json_obj_[name].toArray();

    routine_layout_.Clear();

    for (auto item : routine){
        Exercise* ex = exercise_layout_.GetExerciseByName(item.toString());
        if (ex == nullptr){
            QMessageBox::warning(this, "Unable to load exercise", "Could not load exercise" + item.toString() + ". The exercise may have been renamed or deleted.");
        }
        else{
            exercise_layout_.RemoveExerciseFromGrid(*ex);
            routine_layout_.AddExercise(*ex);
        }

    }
}

void LoadRoutineWindow::OnCancelButtonPressed()
{
    done(QDialog::Rejected);
}

void LoadRoutineWindow::OnDeleteButtonPressed()
{
    auto selection = ui_->routine_list->selectedItems();
    if (selection.empty()) return;

    json_obj_.remove(selection[0]->text());
    delete selection[0];

    QFile file("assets/routines.json");
    if (!file.open(QIODevice::WriteOnly)){
        QMessageBox::warning(this, "Unable to open file", "Could not open routines.json file.");
        return;
    }

    QJsonDocument doc(json_obj_);
    file.write(doc.toJson());
}
