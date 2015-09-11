#ifndef UITAMPERNOWEBCONTENT_H
#define UITAMPERNOWEBCONTENT_H

#include "UiTamperModule.h"
#include <QtWidgets/QPushButton>

class UiTamperNoWebContent : public UiTamperModule
{
	Q_OBJECT

public:
	UiTamperNoWebContent(QWidget *parent, TamperType tamperType);
	~UiTamperNoWebContent();

private:
	QGridLayout* noWebContentLayout;

	QPushButton* noWebContentButton;



	QLabel* buttonImage;
	QPalette buttonImagePaletteActive;
	QPalette buttonImagePaletteInactive;

	void setActive(bool) override;

private slots:
	void onNoTrafficButtonClicked();
};


#endif // UITAMPERNOWEBCONTENT_H
