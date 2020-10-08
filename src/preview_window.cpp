#include "preview_window.h"
#include "exercise_card.h"

PreviewWindow::PreviewWindow(const std::vector<Exercise*>& exercises, QWidget* parent)
    :QDialog(parent)
{
    ui_.setupUi(this);
    //dummy widget needed for scrollarea to work properly
    auto widget = new QWidget(this);
    v_box_ = new QVBoxLayout(this);
    widget->setLayout(v_box_);

    for (const auto& ex : exercises){
        ExerciseCard* card = new ExerciseCard(*ex, this);
        v_box_->addWidget(card);
    }

    ui_.preview_area->setWidget(widget);
}
