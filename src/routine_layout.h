#pragma once

#include <QWidget>
#include <QHBoxLayout>

#include "exercise.h"

class RoutineLayout : public QWidget
{
    Q_OBJECT
public:
    explicit RoutineLayout(QWidget *parent = nullptr);
    virtual ~RoutineLayout() {}

    void AddExercise(Exercise& exercise);
    void Clear();
public slots:
    void SaveRoutine(const QString& name);

private:
    QHBoxLayout* h_box_;

};

