#include "inssidiousui.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	a.setWindowIcon(QIcon(":/InssidiousUi/Inssidious.ico"));

	InssidiousUi w;
	w.show();

	return a.exec();
}
