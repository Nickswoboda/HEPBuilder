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
        Exercise* ex = new Exercise("Howdy" + QString::number(i), "/dev/HEPDesigner/assets/Squat.jpg", "dodasda thisasdhjisadhiasdihsadhias\n\nsdidsaidja\n/nsdsa", {}, this);
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

}
