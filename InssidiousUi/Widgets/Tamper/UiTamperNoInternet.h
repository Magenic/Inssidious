#ifndef UITAMPERNOINTERNET_H
#define UITAMPERNOINTERNET_H

#include "UiTamperModule.h"


class UiTamperNoInternet : public UiTamperModule
{
	Q_OBJECT

public:
	UiTamperNoInternet(QWidget *parent, TamperType tamperType);

private:
	QGridLayout* noInternetLayout;


	QLabel* buttonImage;
	QPalette buttonImagePaletteActive;
	QPalette buttonImagePaletteInactive;

	void setActive(bool) override;

};

#endif // UITAMPERNOINTERNET_H
