#pragma once

#include <QDialog>

#include "ui_previewwindow.h"

class PreviewWindow : public QDialog
{
public:
    PreviewWindow(QWidget* parent);

    Ui::PreviewWindow ui_;
};

