#pragma once

#include <QDialog>
#include <QCheckBox>
#include <QSet>

namespace Ui {
class AddTagsWindow;
}

class AddTagsWindow : public QDialog
{
    Q_OBJECT

public:
    enum class Column{
        BodyPart,
        Type,
        Movement,
        Equipment,
    };

    explicit AddTagsWindow(const QSet<QString>& tags, QWidget *parent = nullptr);
    ~AddTagsWindow();

    QSet<QString> selected_tags_;
private slots:
    void OnAcceptButtonPressed();
    void OnCancelButtonPressed();
private:
    void AddCheckbox(Column column, const QString& text);
    void LoadTagsFromJson();
    void PreselectCheckboxes(const QSet<QString>& tags);
    QSet<QString> GetSelectedTags();

    std::vector<QCheckBox*> tag_boxes_;

    Ui::AddTagsWindow *ui_;
};

