#include "exercise.h"

#include <QPixmap>

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

    tooltip_ = new Tooltip(this);
    tooltip_->hide();
}

void Exercise::enterEvent(QEvent *event)
{
    tooltip_->show();
}

void Exercise::leaveEvent(QEvent *event)
{
    tooltip_->hide();
}
