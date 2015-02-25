/********************************************************************************
** Form generated from reading UI file 'inssidious.ui'
**
** Created by: Qt User Interface Compiler version 5.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INSSIDIOUS_H
#define UI_INSSIDIOUS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Inssidious
{
public:

    void setupUi(QWidget *Inssidious)
    {
        if (Inssidious->objectName().isEmpty())
            Inssidious->setObjectName(QStringLiteral("Inssidious"));
        Inssidious->resize(400, 300);

        retranslateUi(Inssidious);

        QMetaObject::connectSlotsByName(Inssidious);
    } // setupUi

    void retranslateUi(QWidget *Inssidious)
    {
        Inssidious->setWindowTitle(QApplication::translate("Inssidious", "Inssidious", 0));
    } // retranslateUi

};

namespace Ui {
    class Inssidious: public Ui_Inssidious {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INSSIDIOUS_H
