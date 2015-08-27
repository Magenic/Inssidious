#ifndef UITAMPERNODNS_H
#define UITAMPERNODNS_H

#include "UiTamperModule.h"

class UiTamperNoDNS : public UiTamperModule
{
	Q_OBJECT

public:
	UiTamperNoDNS(QWidget *parent, TamperType tamperType);
	~UiTamperNoDNS();

private:
	QLayout* noDNSLayout;
};

#endif // UITAMPERNODNS_H
