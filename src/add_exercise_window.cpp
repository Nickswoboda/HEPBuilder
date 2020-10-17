#include "add_exercise_window.h"
#include "ui_addexercisewindow.h"

#include <QStandardPaths>
#include <QFileDialog>
#include <QPixmap>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

#include "exercise.h"
#include "add_tags_window.h"

AddExerciseWindow::AddExerciseWindow(Exercise* exercise, QWidget *parent) :
    QDialog(parent), exercise_(exercise), ui_(new Ui::AddExerciseWindow)
{
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);

    ui_->setupUi(this);
    ui_->image->setFixedSize(150, 150);

    connect(ui_->add_image_button, SIGNAL(clicked()), this, SLOT(OnAddImageButtonPressed()));
    connect(ui_->accept_button, SIGNAL(clicked()), this, SLOT(OnAcceptButtonPressed()));
    connect(ui_->cancel_button, SIGNAL(clicked()), this, SLOT(OnCancelButtonPressed()));
    connect(ui_->edit_tags_button, SIGNAL(clicked()), this, SLOT(OnEditTagsButtonPressed()));

    if (exercise_ != nullptr){
        ui_->name_edit->setText(exercise_->name_);
        img_path_ = exercise_->img_path_;
        ui_->image->setPixmap(QPixmap(img_path_));
        ui_->instructions_edit->setPlainText(exercise_->instruction_);
        SetCurrentTagsLabel(exercise_->tags_);

        connect(ui_->delete_button, SIGNAL(clicked()), this, SLOT(OnDeleteButtonPressed()));
    }
    else {
        ui_->delete_button->hide();
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
        exercise_ = new Exercise(ui_->name_edit->text(), img_path_, ui_->instructions_edit->toPlainText(), new_tags_, this);
        SaveImage();
        exercise_->SaveToJson();
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

void AddExerciseWindow::SaveImage()
{
    QString old_name = exercise_->name_;
    QString new_img_name = old_name.remove(QRegExp(QString::fromUtf8("[-`~!@#$%^&*()_â€”+=|:;<>Â«Â»,.?/{}\'\"\\\[\\\]\\\\]")));
    QString new_path = "assets/images/" + new_img_name + ".jpg";
    exercise_->pixmap()->save(new_path);
    exercise_->img_path_ = new_path;

}

void AddExerciseWindow::UpdateExercise()
{
    //json is indexed by name, if name is changed, we need to
    if (ui_->name_edit->text() != exercise_->name_){
        exercise_->DeleteFromJson();
    }

    exercise_->name_ = ui_->name_edit->text();
    exercise_->img_path_ = img_path_;
    exercise_->instruction_ = ui_->instructions_edit->toPlainText();
    exercise_->tags_ = new_tags_;

    exercise_->SaveToJson();
}

void AddExerciseWindow::OnEditTagsButtonPressed()
{
    AddTagsWindow tag_window(new_tags_, this);

    if (tag_window.exec() == QDialog::Accepted){
        new_tags_ = tag_window.selected_tags_;
        SetCurrentTagsLabel(new_tags_);
    }

}

void AddExerciseWindow::OnDeleteButtonPressed()
{
    emit DeleteButtonPressed(*exercise_);
    QDialog::done(QDialog::Rejected);
}

void AddExerciseWindow::SetCurrentTagsLabel(const QSet<QString>& tags)
{
    new_tags_ = tags;
    QString text;
    for (const auto& tag : tags){
        text.append(tag + ", ");
    }
    //remove last comma
    text.chop(2);

    ui_->current_tags_label->setText(text);
}


