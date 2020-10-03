#pragma once

#include <QWidget>
#include <QLabel>

class Tooltip : public QWidget
{
public:
    explicit Tooltip(QWidget *parent = nullptr);

    void SetLabels(const QString& name, const QString& instruction);

	QLabel* name_label_;
	QLabel* instruction_label_;

};

