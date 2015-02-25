#include "inssidious.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Inssidious w;
	w.show();
	return a.exec();
}
