#pragma once

#include <QWidget>
#include <QLabel>

class Tooltip : public QWidget
{
public:
    explicit Tooltip(QWidget *parent = nullptr);

	QLabel* name_label_;
	QLabel* instruction_label_;

};

