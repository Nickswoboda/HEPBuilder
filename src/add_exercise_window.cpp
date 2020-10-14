#include "add_exercise_window.h"
#include "ui_addexercisewindow.h"

#include <QStandardPaths>
#include <QFileDialog>
#include <QPixmap>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

#include "exercise.h"

AddExerciseWindow::AddExerciseWindow(Exercise* exercise, QWidget *parent) :
    QDialog(parent), exercise_(exercise), ui_(new Ui::AddExerciseWindow)
{
    ui_->setupUi(this);
    ui_->image->setFixedSize(150, 150);

    connect(ui_->add_image_button, SIGNAL(clicked()), this, SLOT(OnAddImageButtonPressed()));
    connect(ui_->accept_button, SIGNAL(clicked()), this, SLOT(OnAcceptButtonPressed()));
    connect(ui_->cancel_button, SIGNAL(clicked()), this, SLOT(OnCancelButtonPressed()));

    if (exercise_ != nullptr){
        ui_->name_edit->setText(exercise_->name_);
        img_path_ = exercise_->img_path_;
        ui_->image->setPixmap(QPixmap(img_path_));
        ui_->instructions_edit->setPlainText(exercise_->instruction_);
    }
}

AddExerciseWindow::~AddExerciseWindow()
{
    delete ui_;
}

void AddExerciseWindow::OnAddImageButtonPressed()
{
    QString download_dir = QStandardPaths::writableLocation(QStandardPaths::DownloadLocation);
    img_path_ = QFileDialog::getOpenFileName(this, "Add Image", download_dir, "Image File (*.png *.jpg *.bmp)");

    QPixmap img(img_path_);
    if (img.isNull()){
        return;
    }

    ui_->image->setPixmap(img);
}

void AddExerciseWindow::OnAcceptButtonPressed()
{
    if (img_path_.isNull()) return;
    if (ui_->name_edit->text().isEmpty()) return;
    if (ui_->instructions_edit->toPlainText().isEmpty()) return;

    if (exercise_ == nullptr){
        exercise_ = new Exercise(ui_->name_edit->text(), img_path_, ui_->instructions_edit->toPlainText(), {}, this);
        SaveExercise();
    }
    else{
        UpdateExercise();
    }

    done(QDialog::Accepted);
}

void AddExerciseWindow::OnCancelButtonPressed()
{
    done(QDialog::Rejected);
}

void AddExerciseWindow::SaveExercise()
{
    QFile file("assets/exercises.json");

    if (!file.open(QIODevice::ReadOnly)){
        return;
    }

    QByteArray data = file.readAll();
    file.close();
    QJsonDocument doc(QJsonDocument::fromJson(data));
    QJsonObject obj = doc.object();

    QJsonObject ex_obj;
    ex_obj["img path"] = exercise_->img_path_;
    ex_obj["instruction"] = exercise_->instruction_;

    QJsonArray tags_arr;
    for (auto& tag : exercise_->tags_){
        tags_arr.append(tag);
    }
    ex_obj["tags"] = tags_arr;

    obj[exercise_->name_] = ex_obj;
    doc = QJsonDocument(obj);

    if (!file.open(QIODevice::WriteOnly)){
        return;
    }

    file.write(doc.toJson());
    file.close();
}

void AddExerciseWindow::UpdateExercise()
{
    exercise_->name_ = ui_->name_edit->text();
    exercise_->img_path_ = img_path_;
    exercise_->instruction_ = ui_->instructions_edit->toPlainText();
}

