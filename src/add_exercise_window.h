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
    void OnEditTagsButtonPressed();
    void OnDeleteButtonPressed();

private:

    void SaveImage();
    void UpdateExercise();
    void SetCurrentTagsLabel(const QSet<QString>& tags);
    bool IsNameTaken();

    Ui::AddExerciseWindow *ui_;
    QString img_path_;
    QSet<QString> new_tags_;

signals:
    void DeleteButtonPressed(Exercise& exercise);
};

