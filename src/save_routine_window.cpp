#include "save_routine_window.h"
#include "ui_saveroutinewindow.h"

#include <QMessageBox>

SaveRoutineWindow::SaveRoutineWindow(RoutineLayout& layout, QWidget *parent) :
    QDialog(parent), ui_(new Ui::SaveRoutineWindow), layout_(layout)
{
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);

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
    QString name = ui_->input_box->text();
    if (name.isEmpty()){
        QMessageBox::warning(this, "Unable to save routine", "You must enter a routine name to be saved.");
        return;
    }
    if (layout_.SaveRoutine(name)){
        done(QDialog::Accepted);
    }
}

void SaveRoutineWindow::OnCancelButtonPressed()
{
    done(QDialog::Rejected);
}
