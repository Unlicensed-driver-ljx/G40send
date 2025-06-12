/********************************************************************************
** Form generated from reading UI file 'cameraerr.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CAMERAERR_H
#define UI_CAMERAERR_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CameraErr
{
public:
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QLabel *label_2;

    void setupUi(QWidget *CameraErr)
    {
        if (CameraErr->objectName().isEmpty())
            CameraErr->setObjectName(QString::fromUtf8("CameraErr"));
        CameraErr->resize(300, 200);
        verticalLayoutWidget = new QWidget(CameraErr);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(50, 50, 191, 80));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(verticalLayoutWidget);
        label->setObjectName(QString::fromUtf8("label"));
        QFont font;
        font.setPointSize(10);
        label->setFont(font);
        label->setLayoutDirection(Qt::LeftToRight);
        label->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label);

        label_2 = new QLabel(verticalLayoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setFont(font);
        label_2->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label_2);


        retranslateUi(CameraErr);

        QMetaObject::connectSlotsByName(CameraErr);
    } // setupUi

    void retranslateUi(QWidget *CameraErr)
    {
        CameraErr->setWindowTitle(QCoreApplication::translate("CameraErr", "Form", nullptr));
        label->setText(QCoreApplication::translate("CameraErr", "\347\233\270\346\234\272\344\270\215\345\255\230\345\234\250", nullptr));
        label_2->setText(QCoreApplication::translate("CameraErr", "\350\257\267\346\243\200\346\237\245\347\241\254\344\273\266\350\277\236\346\216\245\347\212\266\346\200\201......", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CameraErr: public Ui_CameraErr {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CAMERAERR_H
