#include "save_routine_window.h"
#include "ui_saveroutinewindow.h"

SaveRoutineWindow::SaveRoutineWindow(RoutineLayout& layout, QWidget *parent) :
    QDialog(parent), ui_(new Ui::SaveRoutineWindow), layout_(&layout)
{
    ui_->setupUi(this);

    connect(ui_->add_button, SIGNAL(clicked()), this, SLOT(OnAddButtonPressed()));
    connect(ui_->cancel_button, SIGNAL(clicked()), this, SLOT(OnCancelButtonPressed()));
}

SaveRoutineWindow::~SaveRoutineWindow()
{
    delete ui_;
}

void SaveRoutineWindow::OnAddButtonPressed()
{
    layout_->SaveRoutine(ui_->input_box->text());
    done(QDialog::Accepted);
}

void SaveRoutineWindow::OnCancelButtonPressed()
{
    done(QDialog::Rejected);
}
