#pragma once

#include "ui_exercisecard.h"

#include <QWidget>

#include "exercise.h"
class ExerciseCard : public QWidget
{
public:
    ExerciseCard(const Exercise& exercise, QWidget *parent = nullptr);

    Ui::ExerciseCard ui_;
};

