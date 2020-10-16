#include "tag_search_area.h"

#include <QGridLayout>
#include <QLabel>
#include <QFile>
#include <QCheckBox>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

TagSearchArea::TagSearchArea(QWidget *parent) : QWidget(parent)
{
    QGridLayout* grid = new QGridLayout(this);
    setLayout(grid);

    body_part_tags_ = new QVBoxLayout();
    body_part_tags_->setAlignment(Qt::AlignTop);
    type_tags_ = new QVBoxLayout();
    type_tags_->setAlignment(Qt::AlignTop);
    movement_tags_ = new QVBoxLayout();
    movement_tags_->setAlignment(Qt::AlignTop);
    equipment_tags_ = new QVBoxLayout();
    equipment_tags_->setAlignment(Qt::AlignTop);

    grid->addLayout(body_part_tags_, 0, 0, Qt::AlignTop);
    grid->addLayout(type_tags_, 1, 0, Qt::AlignTop);
    grid->addLayout(movement_tags_, 0, 1, Qt::AlignTop);
    grid->addLayout(equipment_tags_, 1, 1, Qt::AlignTop);

    QLabel* body_part = new QLabel("Body Part", this);
    body_part_tags_->addWidget(body_part);
    QLabel* type = new QLabel("Type", this);
    type_tags_->addWidget(type);
    QLabel* movement = new QLabel("Movement", this);
    movement_tags_->addWidget(movement);
    QLabel* equipment = new QLabel("Equipment", this);
    equipment_tags_->addWidget(equipment);

    SetUpCheckboxes();
}

void TagSearchArea::SetUpCheckboxes()
{
    QFile file("assets/tags.json");
    file.open(QIODevice::ReadOnly);

    QByteArray data = file.readAll();
    file.close();
    QJsonDocument doc(QJsonDocument::fromJson(data));
    QJsonObject obj = doc.object();

    QJsonArray tags = obj["Body Part"].toArray();
    for (auto tag : tags){
        QCheckBox* box = new QCheckBox(tag.toString(), this);
        body_part_tags_->addWidget(box);
        connect(box, SIGNAL(stateChanged(int)), this, SLOT(OnCheckboxPressed(int)));
    }
    tags = obj["Type"].toArray();
    for (auto tag : tags){
        QCheckBox* box = new QCheckBox(tag.toString(), this);
        type_tags_->addWidget(box);
        connect(box, SIGNAL(stateChanged(int)), this, SLOT(OnCheckboxPressed(int)));
    }
    tags = obj["Movement"].toArray();
    for (auto tag : tags){
        QCheckBox* box = new QCheckBox(tag.toString(), this);
        movement_tags_->addWidget(box);
        connect(box, SIGNAL(stateChanged(int)), this, SLOT(OnCheckboxPressed(int)));
    }
    tags = obj["Equipment"].toArray();
    for (auto tag : tags){
        QCheckBox* box = new QCheckBox(tag.toString(), this);
        equipment_tags_->addWidget(box);
        connect(box, SIGNAL(stateChanged(int)), this, SLOT(OnCheckboxPressed(int)));
    }
}

void TagSearchArea::OnCheckboxPressed(int state)
{
    QCheckBox* box = dynamic_cast<QCheckBox*>(sender());

    if (state == Qt::Checked){
        selected_tags_.insert(box->text());
    }
    else{
        selected_tags_.remove(box->text());
    }

    emit TagSearchUpdated(selected_tags_);
}
