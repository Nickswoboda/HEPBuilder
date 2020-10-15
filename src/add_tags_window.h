#pragma once

#include <QDialog>
#include <QCheckBox>

namespace Ui {
class AddTagsWindow;
}

enum Category{
    BodyPart,
    Type,
    Movement,
    Equipment,
};

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

    explicit AddTagsWindow(const std::vector<QString>& tags, QWidget *parent = nullptr);
    ~AddTagsWindow();

    std::vector<QString> selected_tags_;
private slots:
    void OnAcceptButtonPressed();
    void OnCancelButtonPressed();
private:
    void AddCheckbox(Column column, const QString& text);
    void LoadTagsFromJson();
    void PreselectCheckboxes(const std::vector<QString>& tags);
    std::vector<QString> GetSelectedTags();

    std::vector<QCheckBox*> tag_boxes_;

    Ui::AddTagsWindow *ui_;
};

