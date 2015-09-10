#ifndef UITAMPERNOSERVER_H
#define UITAMPERNOSERVER_H

#include "UiTamperModule.h"
#include <QtWidgets/QPushButton>


class UiTamperNoServer : public UiTamperModule
{
	Q_OBJECT

public:
	UiTamperNoServer(QWidget *parent, TamperType tamperType);
	~UiTamperNoServer();


private:
	QGridLayout* noServerLayout;
	
	QPushButton* configServersButton;

	void setActive(bool) override;

private slots:
	void onConfigureServers();
};

#endif // UITAMPERNOSERVER_H
