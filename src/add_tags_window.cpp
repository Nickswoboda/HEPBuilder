#include "add_tags_window.h"
#include "ui_addtagswindow.h"

#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

AddTagsWindow::AddTagsWindow(const std::vector<QString> &tags, QWidget *parent) :
    QDialog(parent),
    ui_(new Ui::AddTagsWindow)
{
    ui_->setupUi(this);
    LoadTagsFromJson();
    if (!tags.empty()){
        PreselectCheckboxes(tags);
    }

    connect(ui_->accept_button, SIGNAL(clicked()), this, SLOT(OnAcceptButtonPressed()));
    connect(ui_->cancel_button, SIGNAL(clicked()), this, SLOT(OnCancelButtonPressed()));
}

AddTagsWindow::~AddTagsWindow()
{
    delete ui_;
}

void AddTagsWindow::LoadTagsFromJson()
{
    QFile file("assets/tags.json");
    file.open(QIODevice::ReadOnly);
    QByteArray data = file.readAll();
    file.close();
    QJsonDocument doc(QJsonDocument::fromJson(data));
    QJsonObject obj = doc.object();

    QJsonArray tags = obj["Body Part"].toArray();
    for (auto tag : tags){
        AddCheckbox(Column::BodyPart, tag.toString());
    }
    tags = obj["Type"].toArray();
    for (auto tag : tags){
        AddCheckbox(Column::Type, tag.toString());
    }
    tags = obj["Movement"].toArray();
    for (auto tag : tags){
        AddCheckbox(Column::Movement, tag.toString());
    }
    tags = obj["Equipment"].toArray();
    for (auto tag : tags){
        AddCheckbox(Column::Equipment, tag.toString());
    }

}

void AddTagsWindow::AddCheckbox(Column column, const QString& text)
{
    QCheckBox* box = new QCheckBox(text, this);
    //used for easier iteration over all boxes
    tag_boxes_.push_back(box);
    switch (column){
    case Column::BodyPart: ui_->body_part_boxes->addWidget(box); break;
    case Column::Type: ui_->type_boxes->addWidget(box); break;
    case Column::Movement: ui_->movement_boxes->addWidget(box); break;
    case Column::Equipment: ui_->equipment_boxes->addWidget(box); break;
    }
}

std::vector<QString> AddTagsWindow::GetSelectedTags()
{
    std::vector<QString> tags;

    for (auto box : tag_boxes_){
        if (box->isChecked()){
            tags.push_back(box->text());
        }
    }

    return tags;
}

void AddTagsWindow::OnAcceptButtonPressed()
{
    selected_tags_ = GetSelectedTags();
    done(QDialog::Accepted);
}

void AddTagsWindow::OnCancelButtonPressed()
{
    done(QDialog::Rejected);
}

void AddTagsWindow::PreselectCheckboxes(const std::vector<QString>& tags)
{
    //TODO: Make tags an unordered set or bitset
    for (auto box : tag_boxes_){
        for (auto& tag : tags){
            if (box->text() == tag){
                box->setCheckState(Qt::Checked);
            }
        }
    }
}
