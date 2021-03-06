#include "routine_layout.h"

#include <QFile>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QMessageBox>

RoutineLayout::RoutineLayout(QWidget *parent) : QWidget(parent)
{
    h_box_ = new QHBoxLayout(this);
    h_box_->setAlignment(Qt::AlignLeft);
    setLayout(h_box_);
}

void RoutineLayout::AddExercise(Exercise& exercise){
   h_box_->addWidget(&exercise);
   exercise.add_button_->setText("-");
   exercise.edit_button_->hide();
}

bool RoutineLayout::IsEmpty()
{
   return h_box_->isEmpty();
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

bool RoutineLayout::SaveRoutine(const QString& name)
{
    QJsonDocument doc;
    QJsonObject obj;

    //load json if it already exists
    QFile file("assets/routines.json");
    if (file.exists()){
        if (!file.open(QIODevice::ReadOnly)){
            QMessageBox::warning(this, "Unable to open file", "Could not open routines.json file");
        }
        else{
            QByteArray data = file.readAll();
            doc = QJsonDocument::fromJson(data);
            obj = doc.object();
            file.close();

            //do not save if a routine already exists with this name
            if (obj.contains(name)){
                QMessageBox::warning(this, "Unable to save routine", "A routine already exists with this name.");
                return false;
            }
        }
    }

    //add json entry for routine
    QJsonArray arr;
    for (int i = 0; i < h_box_->count(); ++i){
        Exercise* ex = static_cast<Exercise*>(h_box_->itemAt(i)->widget());
        arr.append(ex->name_);
    }
    obj[name] = arr;

    //write json back to file
    if (!file.open(QIODevice::WriteOnly)){
        QMessageBox::warning(this, "Unable to open file", "Could not open routines.json file");
        return false;
    }
    doc.setObject(obj);
    file.write(doc.toJson());

    return true;
}

void RoutineLayout::Clear()
{
    //emit exericse button signal to make mainwindow move exercise back into exercise layout
    while(!h_box_->isEmpty()){
        Exercise* ex = static_cast<Exercise*>(h_box_->itemAt(0)->widget());
        emit ex->add_button_->clicked(false);
    }
}
