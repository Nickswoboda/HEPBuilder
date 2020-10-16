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
    connect(ui_->reset_search_button, SIGNAL(clicked()), this, SLOT(OnResetSearchButtonPressed()));
    connect(tag_search_area_, SIGNAL(TagSearchUpdated(QSet<QString>)), exercise_layout_, SLOT(SearchByTags(const QSet<QString>&)));

    LoadExercises();
}

MainWindow::~MainWindow()
{
    delete ui_;
}

void MainWindow::OnExerciseEntered()
{
   Exercise* ex = dynamic_cast<Exercise*>(sender());
   if (!ex) return;

   tooltip_->PlaceOnExercise(*ex);
}

void MainWindow::LoadExercises()
{
    QFile file("assets/exercises.json");
    if (!file.exists()){
        return;
    }

    file.open(QIODevice::ReadOnly);

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
    Exercise* ex = dynamic_cast<Exercise*>(sender()->parent());
    if (!ex) return;

    if (ex->parent() == exercise_layout_){
       routine_layout_->AddExercise(*ex);
       exercise_layout_->RemoveExerciseFromGrid(*ex);
       selected_exercises_.push_back(ex);
    }
    else{
       exercise_layout_->AddExercise(*ex);
    }
}

void MainWindow::OnPreviewButtonPressed()
{
    PreviewWindow preview(selected_exercises_, this);
    preview.exec();
}

void MainWindow::OnSaveButtonPressed()
{
    SaveRoutineWindow save_window(*routine_layout_, this);
    save_window.exec();
}

void MainWindow::OnLoadButtonPressed()
{
    LoadRoutineWindow load_window(*exercise_layout_, *routine_layout_, this);
    load_window.exec();
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
   Exercise* ex = dynamic_cast<Exercise*>(sender()->parent());
   if (!ex) return;

   AddExerciseWindow window(ex, this);
   window.exec();
}


void MainWindow::OnSearchButtonPressed()
{
    exercise_layout_->SearchByName(ui_->search_edit->text());
}

void MainWindow::OnResetSearchButtonPressed()
{
    exercise_layout_->SearchByName("");
}
