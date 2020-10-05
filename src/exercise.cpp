#include "exercise.h"

#include <QPixmap>
#include <QJsonArray>

Exercise::Exercise(const QString& name, const QString& img_path, const QString& instruct, const std::vector<QString>& tags, QWidget *parent)
    :QLabel(parent), name_(name), img_path_(img_path), instruction_(instruct), tags_(tags)
{
    QPixmap img(img_path_);
    if (img.isNull()){
        return;
    }

    setFixedSize(130, 130);
    setScaledContents(true);
    setPixmap(img);

    add_button_ = new QPushButton(this);

}

Exercise::Exercise(const QJsonObject& exercise, QWidget* parent)
    :Exercise(exercise["name"].toString(), exercise["img path"].toString(), exercise["instruction"].toString(), {}, parent)
{
        QJsonArray tags_array = exercise["tags"].toArray();
        for (const auto& tag : tags_array){
            tags_.push_back(tag.toString());
        }
}

void Exercise::enterEvent(QEvent *event)
{
    emit Entered();
}

void Exercise::leaveEvent(QEvent *event)
{
    emit Exited();
}
