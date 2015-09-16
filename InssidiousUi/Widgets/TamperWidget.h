#ifndef TAMPERWIDGETCONTROLLER_H
#define TAMPERWIDGETCONTROLLER_H

#include <QWidget>
#include <QLayout>

#include "Tamper\UiTamperModule.h"	

class TamperWidget : public QWidget
{
	Q_OBJECT

public:
	TamperWidget(QWidget *parent);


	void setImage(QPixmap deviceImage);

signals:
	void tamperStop(TamperWidget*, TamperType);
	void tamperStart(TamperWidget*, TamperType, void* pTamperConfig);

private slots:
	void onTamperModuleStart(UiTamperModule* signaled, void * pTamperConfig);
	void onTamperModuleStop(UiTamperModule* signaled);


private:

	QGridLayout* tamperGridLayout;				

	UiTamperModule* tamperModule[NUM_TAMPER_TYPES];

	QPalette containerPalette;

};

#endif // TAMPERWIDGETCONTROLLER_H
