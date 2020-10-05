#pragma once

#include <QWidget>
#include <QHBoxLayout>

#include "exercise.h"

class RoutineLayout : public QWidget
{
public:
    explicit RoutineLayout(QWidget *parent = nullptr);

    void AddExercise(Exercise& exercise);
private:
    QHBoxLayout* h_box_;

};

