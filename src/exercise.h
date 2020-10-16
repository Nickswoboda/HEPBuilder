#pragma once

#include <QLabel>
#include <QJsonObject>
#include <QPushButton>
#include <QSet>

class Exercise : public QLabel
{
    Q_OBJECT

public:
    Exercise(const QString& name, const QString& img_path, const QString& instruction, const QSet<QString>& tags, QWidget* parent = nullptr);
    Exercise(const QString& name, const QJsonObject& exercise, QWidget* parent);

    void enterEvent(QEvent* event) override;
    void leaveEvent(QEvent* event) override;

    QString name_;
    QString img_path_;
    QString instruction_;
    QSet<QString> tags_;

    QPushButton* add_button_;
    QPushButton* edit_button_;

signals:
    void Entered();
    void Exited();
};
