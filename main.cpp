#include "inssidious.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	InssidiousUi w;
	w.show();
	return a.exec();
}
