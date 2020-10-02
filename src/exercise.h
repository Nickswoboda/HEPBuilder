#pragma once

#include <QLabel>

#include <string>

class Exercise : public QLabel
{
    Q_OBJECT

public:
    Exercise(const QString& name, const QString& img_path, const QString& instruction, const std::vector<QString>& tags, QWidget* parent = nullptr);

    QString name_;
    QString img_path_;
    QString instruction_;
    std::vector<QString> tags_;

signals:
    void Entered();
};
