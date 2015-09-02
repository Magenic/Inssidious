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
	~TamperWidget();

	void setImage(QPixmap deviceImage);


signals:
	void tamperStop(TamperWidget*, TamperType);
	void tamperStart(TamperWidget*, TamperType, void* pTamperConfig);

private slots:
	void onTamperModuleClicked(UiTamperModule* signaled, void* pTamperConfig);

private:

	QGridLayout* tamperGridLayout;				

	UiTamperModule* tamperModule[NUM_TAMPER_TYPES];


	QPalette twContainerPalette;
	QPixmap tcBackgroundImageDevicesPresent = QPixmap(":/Tamper/TamperWidgetBackground.png");	


};

#endif // TAMPERWIDGETCONTROLLER_H
