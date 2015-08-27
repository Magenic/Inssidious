#ifndef UITAMPERCONTENTBLOCKED_H
#define UITAMPERCONTENTBLOCKED_H

#include "UiTamperModule.h"

class UiTamperContentBlocked : public UiTamperModule
{
	Q_OBJECT

public:
	UiTamperContentBlocked(QWidget *parent, TamperType tamperType);
	~UiTamperContentBlocked();

private:
	QLayout* contentBlockedLayout;
};

#endif // UITAMPERCONTENTBLOCKED_H
