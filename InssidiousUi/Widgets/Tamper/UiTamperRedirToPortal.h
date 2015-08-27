#ifndef UITAMPERREDIRTOPORTAL_H
#define UITAMPERREDIRTOPORTAL_H

#include "UiTamperModule.h"

class UiTamperRedirToPortal : public UiTamperModule
{
	Q_OBJECT

public:
	UiTamperRedirToPortal(QWidget *parent, TamperType tamperType);
	~UiTamperRedirToPortal();

private:
	QLayout* redirLayout;
};

#endif // UITAMPERREDIRTOPORTAL_H
