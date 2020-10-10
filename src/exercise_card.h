#pragma once

#include "ui_exercisecard.h"

#include <QWidget>

#include "exercise.h"
class ExerciseCard : public QWidget
{
    Q_OBJECT
public:
    ExerciseCard(const Exercise& exercise, QWidget *parent = nullptr);
    virtual ~ExerciseCard() {}

    Ui::ExerciseCard ui_;
};

