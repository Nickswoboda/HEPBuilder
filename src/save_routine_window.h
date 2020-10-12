#pragma once

#include <QDialog>

#include "routine_layout.h"
namespace Ui {
class SaveRoutineWindow;
}

class SaveRoutineWindow : public QDialog
{
    Q_OBJECT

public:
    explicit SaveRoutineWindow(RoutineLayout& layout, QWidget *parent = nullptr);
    ~SaveRoutineWindow();

public slots:
    void OnAddButtonPressed();
    void OnCancelButtonPressed();
private:
    Ui::SaveRoutineWindow *ui_;
    RoutineLayout& layout_;

};

