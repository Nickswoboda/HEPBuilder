#pragma once

#include <QLabel>
#include <QJsonObject>

#include <string>

#include "tooltip.h"

class Exercise : public QLabel
{
    Q_OBJECT

public:
    Exercise(const QString& name, const QString& img_path, const QString& instruction, const std::vector<QString>& tags, QWidget* parent = nullptr);
    Exercise(const QJsonObject& exercise, QWidget* parent);

    void enterEvent(QEvent* event) override;
    void leaveEvent(QEvent* event) override;

    QString name_;
    QString img_path_;
    QString instruction_;
    std::vector<QString> tags_;

signals:
    void Entered();
    void Exited();
};
