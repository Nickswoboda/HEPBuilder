#pragma once

#include <QDialog>

#include "exercise_layout.h"
#include "routine_layout.h"

#include <QJsonObject>

namespace Ui {
class LoadRoutineWindow;
}

class LoadRoutineWindow : public QDialog
{
    Q_OBJECT

public:
    explicit LoadRoutineWindow(ExerciseLayout& exercise_layout, RoutineLayout& routine_layout, QWidget *parent = nullptr);
    ~LoadRoutineWindow();

    void LoadRoutineNames();

private slots:
    void OnLoadButtonPressed();
    void OnCancelButtonPressed();
    void OnDeleteButtonPressed();

private:
    Ui::LoadRoutineWindow *ui_;
    ExerciseLayout& exercise_layout_;
    RoutineLayout& routine_layout_;

    QJsonObject json_obj_;
};

