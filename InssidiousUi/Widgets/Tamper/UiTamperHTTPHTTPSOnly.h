#ifndef UITAMPERHTTPHTTPSONLY_H
#define UITAMPERHTTPHTTPSONLY_H

#include "UiTamperModule.h"
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QPushButton>

class UiTamperHTTPHTTPSOnly : public UiTamperModule
{
	Q_OBJECT

public:
	UiTamperHTTPHTTPSOnly(QWidget *parent, TamperType tamperType);
	~UiTamperHTTPHTTPSOnly();

private:
	QGridLayout* httpHTTPSOnlyLayout;
	QButtonGroup* qButtonGroup;
	QPushButton* bHTTPOnly;
	QPushButton* bHTTPSOnly;
	QPushButton* bHTTPHTTPSOnly;
};

#endif // UITAMPERHTTPHTTPSONLY_H
