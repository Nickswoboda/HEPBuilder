#include "preview_window.h"
#include "exercise_card.h"

#include <QtPrintSupport/QPrintPreviewDialog>
#include <QPainter>
#include <iostream>

PreviewWindow::PreviewWindow(const std::vector<Exercise*>& exercises, QWidget* parent)
    :QDialog(parent)
{
    ui_.setupUi(this);
    //dummy widget needed for scrollarea to work properly
    auto widget = new QWidget(this);
    v_box_ = new QVBoxLayout();
    widget->setLayout(v_box_);
    v_box_->setAlignment(Qt::AlignTop);
    ui_.preview_area->setWidget(widget);
    for (const auto& ex : exercises){
        ExerciseCard* card = new ExerciseCard(*ex, widget);
        widget->layout()->addWidget(card);
    }

    connect(ui_.buttonBox, SIGNAL(accepted()), this, SLOT(OnPrintPressed()));
}

void PreviewWindow::OnPrintPressed()
{
    QPrintPreviewDialog* preview = new QPrintPreviewDialog(this);
    connect(preview, SIGNAL(paintRequested(QPrinter*)), this, SLOT(DrawPrintPreview(QPrinter*)));
    preview->exec();
}

void PreviewWindow::DrawPrintPreview(QPrinter* printer)
{
    QPainter painter(printer);
    const int ex_per_page = 7;

    for (int i = 0; i < v_box_->count(); ++i){
        QWidget* card = v_box_->itemAt(i)->widget();
        card->render(&painter);
        painter.translate(0, 180);
        if (i == ex_per_page){
            printer->newPage();
        //move painter back to top of page
            painter.translate(0, -180 * 8);
        }
    }
}
