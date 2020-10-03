#pragma once

#include <QWidget>
#include <QGridLayout>

class ExerciseLayout : public QWidget
{
    Q_OBJECT
public:
    explicit ExerciseLayout(QWidget* parent);

    void AddExercise(QWidget* exercise);
private:
    QGridLayout* grid_;
    const int max_cols_ = 8;
    int curr_row_ = 1;
    int curr_col_ = 1;
signals:

};

