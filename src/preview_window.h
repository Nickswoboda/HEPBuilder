#pragma once

#include "ui_previewwindow.h"

#include <QDialog>
#include <QVBoxLayout>

#include <vector>

#include "exercise.h"

class PreviewWindow : public QDialog
{
public:
    PreviewWindow(const std::vector<Exercise*>& exercises, QWidget* parent);

    Ui::PreviewWindow ui_;
    QVBoxLayout* v_box_;
};

