#pragma once

#include <QWidget>
#include <QLabel>

#include "exercise.h"

class Tooltip : public QWidget
{
public:
    explicit Tooltip(QWidget *parent = nullptr);

    void PlaceOnExercise(const Exercise& ex);

    QLabel* name_label_;
	QLabel* instruction_label_;
};

