#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>

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

    tooltip_ = new Tooltip(this);
    tooltip_->hide();

    connect(ui_->preview_button, SIGNAL(clicked()), this, SLOT(OnPreviewButtonPressed()));
    connect(ui_->load_button, SIGNAL(clicked()), this, SLOT(OnLoadButtonPressed()));
    connect(ui_->save_button, SIGNAL(clicked()), this, SLOT(OnSaveButtonPressed()));
    connect(ui_->create_exercise_button, SIGNAL(clicked()), this, SLOT(OnCreateExerciseButtonPressed()));

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

   QPoint mouse_pos = mapFromGlobal(QCursor::pos());
   QPoint mouse_pos_on_ex = ex->mapFromGlobal(QCursor::pos());

   //make sure tooltip is placed below the exercise that is being hovered
   mouse_pos.rx() -= mouse_pos_on_ex.x();
   mouse_pos.ry() += ex->geometry().height() - mouse_pos_on_ex.y();

   //make sure tooltip is placed completely within the main window
   if (mouse_pos.x() + tooltip_->geometry().width() > geometry().width()){
       mouse_pos.rx() = geometry().width() - tooltip_->geometry().width();
   }
   if (mouse_pos.y() + tooltip_->geometry().height() > geometry().height()){
       mouse_pos.ry() = geometry().height() - tooltip_->geometry().height();
   }
   tooltip_->move(mouse_pos.x(), mouse_pos.y());

   tooltip_->SetLabels(ex->name_, ex->instruction_);
   tooltip_->show();
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
        Exercise* exercise = new Exercise(name, exercises[name].toObject(), this);
        InitializeExercise(*exercise);
    }

   file.close();
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
       selected_exercises_.push_back(ex);
    }
    else{
       exercise_layout_->AddExercise(*ex);
    }
}

void MainWindow::OnPreviewButtonPressed()
{
    PreviewWindow* preview = new PreviewWindow(selected_exercises_, this);
    preview->exec();
}

void MainWindow::OnSaveButtonPressed()
{
    SaveRoutineWindow* save_window = new SaveRoutineWindow(*routine_layout_, this);
    save_window->exec();
}

void MainWindow::OnLoadButtonPressed()
{
    LoadRoutineWindow* load_window = new LoadRoutineWindow(*exercise_layout_, *routine_layout_, this);
    load_window->exec();
}

void MainWindow::OnCreateExerciseButtonPressed()
{
    AddExerciseWindow* window = new AddExerciseWindow(nullptr, this);
    if (window->exec() == QDialog::Accepted){
        InitializeExercise(*window->exercise_);
    }
}

void MainWindow::OnEditExercisePressed()
{
   Exercise* ex = dynamic_cast<Exercise*>(sender()->parent());
   if (!ex) return;

   AddExerciseWindow* window = new AddExerciseWindow(ex, this);
   window->exec();
}
