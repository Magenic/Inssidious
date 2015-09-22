#ifndef UITAMPERNOSERVER_H
#define UITAMPERNOSERVER_H

#include "UiTamperModule.h"


class UiTamperNoServer : public UiTamperModule
{
	Q_OBJECT

public:
	UiTamperNoServer(QWidget *parent, TamperType tamperType);



private:
	QGridLayout* noServerLayout;
	
	QLabel* buttonImage;
	QPalette buttonImagePaletteActive;
	QPalette buttonImagePaletteInactive;

	QList<QString> dialogServerList;
	unsigned int serverListVersion;

	void setActive(bool) override;

};

#endif // UITAMPERNOSERVER_H
