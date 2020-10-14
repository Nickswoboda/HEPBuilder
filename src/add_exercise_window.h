#pragma once

#include <QDialog>

#include "exercise.h"

namespace Ui {
class AddExerciseWindow;
}

class AddExerciseWindow : public QDialog
{
    Q_OBJECT

public:
    explicit AddExerciseWindow(Exercise* exercise = nullptr, QWidget *parent = nullptr);
    ~AddExerciseWindow();

    Exercise* exercise_ = nullptr;


private slots:
    void OnAddImageButtonPressed();
    void OnAcceptButtonPressed();
    void OnCancelButtonPressed();

private:

    void SaveExercise();
    void UpdateExercise();

    Ui::AddExerciseWindow *ui_;
    QString img_path_;
};

