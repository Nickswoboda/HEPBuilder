#pragma once

#include <QMainWindow>

#include "exercise_layout.h"
#include "routine_layout.h"
#include "tag_search_area.h"
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

    void LoadExercises();
    void InitializeExercise(Exercise& exercise);

private slots:
    void OnExerciseEntered();
    void OnExerciseExited() {tooltip_->hide();}

    void OnAddToRoutinePressed();
    void OnPreviewButtonPressed();

    void OnSaveButtonPressed();
    void OnLoadButtonPressed();

    void OnCreateExerciseButtonPressed();
    void OnEditExercisePressed();

    void OnSearchButtonPressed();
    void OnResetSearchButtonPressed();

private:
    Ui::MainWindow *ui_;
    ExerciseLayout* exercise_layout_;
    RoutineLayout* routine_layout_;
    TagSearchArea* tag_search_area_;

    Tooltip* tooltip_;
    std::vector<Exercise*> selected_exercises_;
};
