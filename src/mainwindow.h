#pragma once

#include <QMainWindow>

#include "exercise_layout.h"
#include "tooltip.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void OnExerciseEntered();
    void OnExerciseExited() {tooltip_->hide();}

private:
    Ui::MainWindow *ui;
    ExerciseLayout* exercise_layout_;
    Tooltip* tooltip_;
};
