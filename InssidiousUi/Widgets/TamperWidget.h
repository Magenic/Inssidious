#ifndef TAMPERWIDGETCONTROLLER_H
#define TAMPERWIDGETCONTROLLER_H

#include <QWidget>
#include <QLayout>

#include "Tamper\UiTamperModule.h"			//

class TamperWidget : public QWidget
{
	Q_OBJECT

public:
	TamperWidget(QWidget *parent);
	~TamperWidget();

signals:
	void tamperStop(TamperWidget*, TamperType);
	void tamperStart(TamperWidget*, TamperType);

private slots:
	void onTamperModuleClicked(UiTamperModule* signaled);

private:

	QVBoxLayout* twContainerVLayout;				//VBoxLayout to lay out the tamper widgets
	QLabel* tamperClassLabel[NUM_TAMPER_CLASSES];
	QHBoxLayout* tamperClassLayout[NUM_TAMPER_CLASSES];
	UiTamperModule* tamperModule[NUM_TAMPER_TYPES];


	QPalette twContainerPalette;
	QPixmap tcBackgroundImageDevicesPresent = QPixmap(":/Tabs/TabsDevicesPresent.png");	//Draws a bordered rectangle
	QFont tamperClassFont;

};

#endif // TAMPERWIDGETCONTROLLER_H
