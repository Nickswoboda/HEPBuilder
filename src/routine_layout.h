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
    std::vector<Exercise*> GetExercises();
public slots:
    void SaveRoutine(const QString& name);
    void Clear();

private:
    QHBoxLayout* h_box_;

};

