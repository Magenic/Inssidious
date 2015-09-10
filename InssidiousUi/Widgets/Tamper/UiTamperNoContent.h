#ifndef UITAMPERNOCONTENT_H
#define UITAMPERNOCONTENT_H

#include "UiTamperModule.h"
#include <QtWidgets/QPushButton>

class UiTamperNoContent : public UiTamperModule
{
	Q_OBJECT

public:
	UiTamperNoContent(QWidget *parent, TamperType tamperType);
	~UiTamperNoContent();

private:
	QGridLayout* noContentLayout;

	QPushButton* noContentButton;

	void setActive(bool) override;

private slots:
	void onNoTrafficButtonClicked();
};


#endif // UITAMPERNOCONTENT_H
