#pragma once

#include "ui_previewwindow.h"

#include <QDialog>
#include <QVBoxLayout>
#include <QtPrintSupport/QPrinter>

#include <vector>

#include "exercise.h"

class PreviewWindow : public QDialog
{
    Q_OBJECT
public:
    PreviewWindow(const std::vector<Exercise*>& exercises, QWidget* parent);
    virtual ~PreviewWindow() {};

public slots:
    void OnPrintPressed();
    void DrawPrintPreview(QPrinter* printer);

private:
    Ui::PreviewWindow ui_;
    QVBoxLayout* v_box_;
};

