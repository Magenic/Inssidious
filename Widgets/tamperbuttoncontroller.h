#ifndef TAMPERBUTTONCONTROLLER_H
#define TAMPERBUTTONCONTROLLER_H

#include <QtWidgets/QWidget>
#include "TamperButtons\tamperbutton.h"


class TamperButtonController : public QWidget
{
	Q_OBJECT

public:
	TamperButtonController(QWidget *parent);
	~TamperButtonController();


private slots:
	void onTamperButtonClicked(TamperButton*);


private:
	
};

#endif // TAMPERBUTTONCONTROLLER_H
