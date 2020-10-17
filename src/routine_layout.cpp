#include "routine_layout.h"

#include <QFile>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>

RoutineLayout::RoutineLayout(QWidget *parent) : QWidget(parent)
{
    h_box_ = new QHBoxLayout(this);
    setLayout(h_box_);
}

void RoutineLayout::AddExercise(Exercise& exercise){
   h_box_->addWidget(&exercise);
   exercise.add_button_->setText("-");
}

std::vector<Exercise*> RoutineLayout::GetExercises()
{
    std::vector<Exercise*> exercises;

    for (int i = 0; i < h_box_->count(); ++i){
        Exercise* ex = static_cast<Exercise*>(h_box_->itemAt(i)->widget());
        exercises.push_back(ex);
    }

    return exercises;
}

void RoutineLayout::SaveRoutine(const QString& name)
{
    QJsonDocument doc;
    QJsonObject obj;

    //load json if it already exists
    QFile file("assets/routines.json");
    if (file.exists()){
        file.open(QIODevice::ReadOnly);
        QByteArray data = file.readAll();
        doc = QJsonDocument::fromJson(data);
        obj = doc.object();
        file.close();
    }

    //add json entry for routine
    QJsonArray arr;
    for (int i = 0; i < h_box_->count(); ++i){
        Exercise* ex = static_cast<Exercise*>(h_box_->itemAt(i)->widget());
        arr.append(ex->name_);
    }
    obj[name] = arr;

    //write json back to file
    file.open(QIODevice::WriteOnly);
    doc.setObject(obj);
    file.write(doc.toJson());
    file.close();
}

void RoutineLayout::Clear()
{
    //emit exericse button signal to make mainwindow move exercise back into exercise layout
    while(!h_box_->isEmpty()){
        Exercise* ex = static_cast<Exercise*>(h_box_->itemAt(0)->widget());
        emit ex->add_button_->clicked(false);
    }
}
