#ifndef NEWDEVICEWIDGET_H
#define NEWDEVICEWIDGET_H

#include <QWidget>
#include <QListView>
#include <QStandardItemModel>
#include <QtWidgets/QLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>

class NewDeviceWidget : public QWidget
{
	Q_OBJECT

public:
	NewDeviceWidget(QWidget *parent, QString MACAddress);
	~NewDeviceWidget();

signals:
	void setDeviceInfo(QString MACAddress, QString deviceName, QPixmap deviceImage);


private:
	QVBoxLayout* ndlayout;

	QString MAC;

	QPalette backgroundPalette;
	QPixmap backgroundImage = QPixmap(":/Tabs/TabsDevicesPresent.png");


	QPushButton* setNewDeviceInfoButton;		//Set QPushButton in the initial new device layout

	QPalette descriptionTextPalette;			//Palette for grey description text
	QPalette errorTextPalette;					//Palette for red error text

	QLabel* deviceNameTextLabel;				//Description text label
	QLineEdit* deviceNameLineEdit;				//Editable field to specify the device name

	QLabel* deviceIconImageListTextLabel;		//Description text label
	QListView* deviceIconImageList;				//List of device icons
	QStandardItemModel *iStandardModel;			//Item model


private slots:
	void onSetButtonClicked();

};

#endif // NEWDEVICEWIDGET_H
