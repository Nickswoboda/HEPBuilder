#pragma once

#include <QWidget>

#include "exercise_card.h"

namespace Ui {
class PrintCard;
}

class PrintCard : public QWidget
{
    Q_OBJECT

public:
    explicit PrintCard(const ExerciseCard& card, QWidget *parent = nullptr);
    ~PrintCard();

private:
    Ui::PrintCard *ui_;
};

