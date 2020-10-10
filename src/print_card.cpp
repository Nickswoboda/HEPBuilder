#include "print_card.h"
#include "ui_printcard.h"

PrintCard::PrintCard(const ExerciseCard& card, QWidget *parent) :
    QWidget(parent),
    ui_(new Ui::PrintCard)
{
    ui_->setupUi(this);
    ui_->image->setPixmap(*(card.ui_.image->pixmap()));
    ui_->text->setText(card.ui_.text->text());
    setStyleSheet("background-color: white");

    ui_->sets->setText("Sets: " + QString::number(card.ui_.sets_box->value()));
    ui_->reps->setText("Reps: " + QString::number(card.ui_.reps_box->value()));
    ui_->hold->setText("Hold for " + QString::number(card.ui_.hold_box->value()) + "seconds");

}

PrintCard::~PrintCard()
{
    delete ui_;
}

