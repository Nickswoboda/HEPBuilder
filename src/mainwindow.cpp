#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "exercise.h"
#include "exercise_layout.h"

#include "tooltip.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    exercise_layout_ = new ExerciseLayout(this);
    ui->exercise_area->setWidgetResizable(true);
    ui->exercise_area->setWidget(exercise_layout_);

    for (int i = 0; i < 32; ++i){
        Exercise* ex = new Exercise("Howdy", "/dev/HEPBuilder/assets/Squat.jpg", "do this", {}, this);
        connect(ex, SIGNAL(Entered()), this, SLOT(OnExerciseEntered()));
        connect(ex, SIGNAL(Exited()), this, SLOT(OnExerciseExited()));
        exercise_layout_->AddExercise(ex);
    }

    tooltip_ = new Tooltip(this);
    tooltip_->hide();
}

MainWindow::~MainWindow()
{
    delete ui;
}

