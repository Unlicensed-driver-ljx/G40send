/********************************************************************************
** Form generated from reading UI file 'smallimagedisplayform.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SMALLIMAGEDISPLAYFORM_H
#define UI_SMALLIMAGEDISPLAYFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SmallImageDisplayForm
{
public:
    QGridLayout *gridLayout;
    QLabel *label;

    void setupUi(QWidget *SmallImageDisplayForm)
    {
        if (SmallImageDisplayForm->objectName().isEmpty())
            SmallImageDisplayForm->setObjectName(QString::fromUtf8("SmallImageDisplayForm"));
        SmallImageDisplayForm->resize(12, 14);
        SmallImageDisplayForm->setMaximumSize(QSize(640, 480));
        SmallImageDisplayForm->setAutoFillBackground(false);
        SmallImageDisplayForm->setStyleSheet(QString::fromUtf8("background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(255, 0, 0, 255), stop:0.166 rgba(255, 255, 0, 255), stop:0.333 rgba(0, 255, 0, 255), stop:0.5 rgba(0, 255, 255, 255), stop:0.666 rgba(0, 0, 255, 255), stop:0.833 rgba(255, 0, 255, 255), stop:1 rgba(255, 0, 0, 255));"));
        gridLayout = new QGridLayout(SmallImageDisplayForm);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(SmallImageDisplayForm);
        label->setObjectName(QString::fromUtf8("label"));
        label->setStyleSheet(QString::fromUtf8(""));
        label->setScaledContents(true);
        label->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label, 0, 0, 1, 1);


        retranslateUi(SmallImageDisplayForm);

        QMetaObject::connectSlotsByName(SmallImageDisplayForm);
    } // setupUi

    void retranslateUi(QWidget *SmallImageDisplayForm)
    {
        SmallImageDisplayForm->setWindowTitle(QCoreApplication::translate("SmallImageDisplayForm", "Form", nullptr));
        label->setText(QCoreApplication::translate("SmallImageDisplayForm", "IR", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SmallImageDisplayForm: public Ui_SmallImageDisplayForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SMALLIMAGEDISPLAYFORM_H
