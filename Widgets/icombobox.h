#ifndef ICOMBOBOX_H
#define ICOMBOBOX_H

#include <QObject>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLineEdit>
#include <QtCore/QEvent>

class IComboBox : public QComboBox
{
	Q_OBJECT

public:

	/* Resolves a drawing bug with Qt and extended frame windows by pulling popup back in */

	void IComboBox::showPopup() {
			QComboBox::showPopup();
			QWidget *popup = this->findChild<QFrame*>();
			popup->move(popup->x() -8, popup->y() - 30);
		}


	/* Show pop up on all mouseReleaseEvents received by QComboBox */

	void IComboBox::mouseReleaseEvent(QMouseEvent *event)
	{
		IComboBox::showPopup();
	}


private:
	
};

#endif // ICOMBOBOX_H
