#ifndef INSSIDIOUS_H
#define INSSIDIOUS_H

#include <QWidget>
#include "ui_inssidious.h"

class Inssidious : public QWidget
{
	Q_OBJECT

public:
	Inssidious(QWidget *parent = 0);
	~Inssidious();

private:
	Ui::Inssidious ui;
};

#endif // INSSIDIOUS_H