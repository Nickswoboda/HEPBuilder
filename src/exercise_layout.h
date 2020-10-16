#pragma once

#include <QWidget>
#include <QGridLayout>
#include <QHash>

#include "exercise.h"

class ExerciseLayout : public QWidget
{
    Q_OBJECT
public:
    explicit ExerciseLayout(QWidget* parent);

    void AddExercise(Exercise& exercise);
    void AddExerciseToGrid(Exercise& exercise);
    void RemoveExerciseFromGrid(Exercise& exercise);
    void RemoveAllItemsFromGrid();
    Exercise* GetExerciseByName(const QString& name);

public slots:
    void SearchByName(const QString& name);
    void SearchByTags(const QSet<QString>& tags);
private:
    QGridLayout* grid_;
    QHash<QString, Exercise*> exercises_;
    const int max_cols_ = 8;
    int curr_row_ = 1;
    int curr_col_ = 1;
signals:

};

