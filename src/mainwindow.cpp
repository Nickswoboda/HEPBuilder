#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "exercise.h"
#include "exercise_layout.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ExerciseLayout* exercise_layout = new ExerciseLayout(this);
    ui->exercise_area->setWidgetResizable(true);
    ui->exercise_area->setWidget(exercise_layout);
    Exercise* ex = new Exercise("Howdy", "/dev/HEPBuilder/assets/Squat.jpg", "do this", {}, this);
    exercise_layout->AddExercise(ex);
}

MainWindow::~MainWindow()
{
    delete ui;
}

