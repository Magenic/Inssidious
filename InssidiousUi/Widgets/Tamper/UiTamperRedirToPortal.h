#ifndef UITAMPERREDIRTOPORTAL_H
#define UITAMPERREDIRTOPORTAL_H

#include "UiTamperModule.h"
#include <QtWidgets/QPushButton>

class UiTamperRedirToPortal : public UiTamperModule
{
	Q_OBJECT

public:
	UiTamperRedirToPortal(QWidget *parent, TamperType tamperType);
	~UiTamperRedirToPortal();

private:
	QGridLayout* redirToPortalLayout;
	QPushButton* redirToPortalButton;
};

#endif // UITAMPERREDIRTOPORTAL_H
