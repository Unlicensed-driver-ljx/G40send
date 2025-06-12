/********************************************************************************
** Form generated from reading UI file 'newwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NEWWINDOW_H
#define UI_NEWWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_newWindow
{
public:
    QLabel *label;

    void setupUi(QWidget *newWindow)
    {
        if (newWindow->objectName().isEmpty())
            newWindow->setObjectName(QString::fromUtf8("newWindow"));
        newWindow->resize(400, 300);
        label = new QLabel(newWindow);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(110, 80, 171, 161));

        retranslateUi(newWindow);

        QMetaObject::connectSlotsByName(newWindow);
    } // setupUi

    void retranslateUi(QWidget *newWindow)
    {
        newWindow->setWindowTitle(QApplication::translate("newWindow", "Form", nullptr));
        label->setText(QApplication::translate("newWindow", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class newWindow: public Ui_newWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NEWWINDOW_H
