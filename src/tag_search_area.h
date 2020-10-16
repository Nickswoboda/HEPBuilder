#pragma once

#include <QWidget>
#include <QSet>
#include <QVBoxLayout>


class TagSearchArea : public QWidget
{
    Q_OBJECT
public:
    explicit TagSearchArea(QWidget *parent = nullptr);
private:
    void SetUpCheckboxes();

    QSet<QString> selected_tags_;

    QVBoxLayout* body_part_tags_;
    QVBoxLayout* type_tags_;
    QVBoxLayout* movement_tags_;
    QVBoxLayout* equipment_tags_;

private slots:
    void OnCheckboxPressed(int state);

signals:
    void TagSearchUpdated(QSet<QString> tags);
};

