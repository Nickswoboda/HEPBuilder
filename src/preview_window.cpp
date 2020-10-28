#include "preview_window.h"

#include <QtPrintSupport/QPrintPreviewDialog>
#include <QPainter>
#include <iostream>
#include <QRect>
#include <QScreen>

#include "exercise_card.h"
#include "print_card.h"

PreviewWindow::PreviewWindow(const std::vector<Exercise*>& exercises, QWidget* parent)
    :QDialog(parent)
{
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);

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
    QPrinter printer(QPrinter::HighResolution);
    printer.setColorMode(QPrinter::GrayScale);
    printer.setPageMargins(16,16,16,16, QPrinter::Millimeter);

    QPrintPreviewDialog preview(&printer, this);
    connect(&preview, SIGNAL(paintRequested(QPrinter*)), this, SLOT(DrawPrintPreview(QPrinter*)));
    preview.exec();
}

void PreviewWindow::DrawPrintPreview(QPrinter* printer)
{
    QPainter painter(printer);

    //scale widget to printer resolution
    //700 is the size of the printcard
    qreal x_scale = printer->pageRect().width() / 700.0;
    painter.scale(x_scale, x_scale);
    painter.setPen(QPen(Qt::gray, 4));
    //save initial position at top of page
    painter.save();

    const int ex_per_page = 5;
    int ex_on_page = 0;

    for (int i = 0; i < v_box_->count(); ++i){

        if (ex_on_page == ex_per_page ){
            printer->newPage();
            //move painter back to top of page and save again for next page
            painter.restore();
            painter.save();
            ex_on_page = 0;
        }
        else if (ex_on_page != 0){
            //draw borderline
            painter.drawLine(0, 0, 700, 0);
            painter.translate(0, 5);
        }

        ExerciseCard* card = static_cast<ExerciseCard*>(v_box_->itemAt(i)->widget());
        PrintCard print_card(*card, this);
        print_card.render(&painter);
        ++ex_on_page;
        painter.translate(0, 185);


    }
}
