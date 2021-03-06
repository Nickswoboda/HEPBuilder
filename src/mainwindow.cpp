#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMessageBox>

#include "exercise.h"
#include "exercise_layout.h"
#include "preview_window.h"
#include "tooltip.h"
#include "save_routine_window.h"
#include "load_routine_window.h"
#include "add_exercise_window.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui_(new Ui::MainWindow)
{
    ui_->setupUi(this);
    exercise_layout_ = new ExerciseLayout(this);
    ui_->exercise_area->setWidgetResizable(true);
    ui_->exercise_area->setWidget(exercise_layout_);

    routine_layout_ = new RoutineLayout(this);
    ui_->routine_area->setWidgetResizable(true);
    ui_->routine_area->setWidget(routine_layout_);

    tag_search_area_ = new TagSearchArea(this);
    ui_->search_by_tag_layout->addWidget(tag_search_area_);

    tooltip_ = new Tooltip(this);

    connect(ui_->preview_button, SIGNAL(clicked()), this, SLOT(OnPreviewButtonPressed()));
    connect(ui_->load_button, SIGNAL(clicked()), this, SLOT(OnLoadButtonPressed()));
    connect(ui_->save_button, SIGNAL(clicked()), this, SLOT(OnSaveButtonPressed()));
    connect(ui_->create_exercise_button, SIGNAL(clicked()), this, SLOT(OnCreateExerciseButtonPressed()));
    connect(ui_->search_button, SIGNAL(clicked()), this, SLOT(OnSearchButtonPressed()));
    connect(ui_->search_edit, SIGNAL(returnPressed()), this, SLOT(OnSearchButtonPressed()));
    connect(ui_->reset_search_button, SIGNAL(clicked()), this, SLOT(OnResetSearchButtonPressed()));
    connect(tag_search_area_, SIGNAL(TagSearchUpdated(QSet<QString>)), exercise_layout_, SLOT(SearchByTags(const QSet<QString>&)));
    connect(ui_->clear_routine_button, SIGNAL(clicked()), routine_layout_, SLOT(Clear()));

    LoadExercises();
}

MainWindow::~MainWindow()
{
    delete ui_;
}

void MainWindow::OnExerciseEntered()
{
   Exercise* ex = static_cast<Exercise*>(sender());
   tooltip_->PlaceOnExercise(*ex);
}

void MainWindow::LoadExercises()
{
    QFile file("assets/exercises.json");
    if (!file.open(QIODevice::ReadOnly)){
        QMessageBox::warning(this, "Unable to open file", "Could not load exercises from exercises.json file.");
    }

    QByteArray data = file.readAll();
    QJsonDocument doc(QJsonDocument::fromJson(data));
    QJsonObject exercises = doc.object();

    for (const auto& name : exercises.keys()){
        //exercise may throw if unable to load image
        try {
        Exercise* exercise = new Exercise(name, exercises[name].toObject(), this);
        InitializeExercise(*exercise);
        }  catch (std::exception& e) {
            QMessageBox::warning(this, "Unable to load exercise", QString::fromStdString(e.what()));
        }
    }
}

void MainWindow::InitializeExercise(Exercise &exercise)
{
    connect(&exercise, SIGNAL(Entered()), this, SLOT(OnExerciseEntered()));
    connect(&exercise, SIGNAL(Exited()), this, SLOT(OnExerciseExited()));
    connect(exercise.add_button_, SIGNAL(clicked()), this, SLOT(OnAddToRoutinePressed()));
    connect(exercise.edit_button_, SIGNAL(clicked()), this, SLOT(OnEditExercisePressed()));
    exercise_layout_->AddExercise(exercise);
}

void MainWindow::OnAddToRoutinePressed()
{
    Exercise* ex = static_cast<Exercise*>(sender()->parent());

    if (ex->parent() == exercise_layout_){
       exercise_layout_->RemoveExerciseFromGrid(*ex);
       routine_layout_->AddExercise(*ex);
    }
    else{
       exercise_layout_->AddExercise(*ex);
    }
}

void MainWindow::OnPreviewButtonPressed()
{
    if (routine_layout_->IsEmpty()){
        QMessageBox::information(this, "No exercises to preview", "There are no exercises in the routine to preview.");
        return;
    }

    std::vector<Exercise*> routine_exercises = routine_layout_->GetExercises();
    PreviewWindow preview(routine_exercises, this);
    preview.exec();
}

void MainWindow::OnSaveButtonPressed()
{
    if (routine_layout_->IsEmpty()){
        QMessageBox::information(this, "No exercises to save", "There are no exercises in the routine to save.");
        return;
    }

    SaveRoutineWindow save_window(*routine_layout_, this);
    save_window.exec();
}

void MainWindow::OnLoadButtonPressed()
{
    LoadRoutineWindow load_window(*exercise_layout_, *routine_layout_, this);
    //if routine names did not load, then there is no point showing empty list
    if (load_window.LoadRoutineNames()){
        load_window.exec();
    }
}

void MainWindow::OnCreateExerciseButtonPressed()
{
    AddExerciseWindow window(nullptr, this);
    if (window.exec() == QDialog::Accepted){
        InitializeExercise(*window.exercise_);
    }
}

void MainWindow::OnEditExercisePressed()
{
   Exercise* ex = static_cast<Exercise*>(sender()->parent());

   AddExerciseWindow window(ex, this);
   connect(&window, SIGNAL(DeleteButtonPressed(Exercise&)), exercise_layout_, SLOT(DeleteExercise(Exercise&)));
   window.exec();
}


void MainWindow::OnSearchButtonPressed()
{
    exercise_layout_->SearchByName(ui_->search_edit->text());
}

void MainWindow::OnResetSearchButtonPressed()
{
    exercise_layout_->SearchByName("");
    ui_->search_edit->setText("");
}
