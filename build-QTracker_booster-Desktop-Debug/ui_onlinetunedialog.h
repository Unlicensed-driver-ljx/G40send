/********************************************************************************
** Form generated from reading UI file 'onlinetunedialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ONLINETUNEDIALOG_H
#define UI_ONLINETUNEDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_OnlineTuneDialog
{
public:
    QGridLayout *gridLayout;
    QTabWidget *tabWidget;
    QWidget *tab;
    QGridLayout *gridLayout_10;
    QGroupBox *groupBox_34;
    QPushButton *pushButtonCameraState;
    QGroupBox *groupBox_3;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout_2;
    QComboBox *comboBoxCameraLinkMode;
    QLineEdit *lineEditResolutionW;
    QLabel *label_10;
    QLabel *label_16;
    QPushButton *btnReceive;
    QSpinBox *spinBoxImageBit;
    QSpinBox *spinBoxImageTap;
    QLabel *label_15;
    QLabel *label_14;
    QLabel *label_5;
    QLineEdit *lineEditResolutionH;
    QComboBox *comboBoxImageFormat;
    QLabel *label_17;
    QLabel *label_20;
    QPushButton *btnSend;
    QSpacerItem *verticalSpacer_2;

    void setupUi(QDialog *OnlineTuneDialog)
    {
        if (OnlineTuneDialog->objectName().isEmpty())
            OnlineTuneDialog->setObjectName(QString::fromUtf8("OnlineTuneDialog"));
        OnlineTuneDialog->resize(400, 1117);
        OnlineTuneDialog->setMinimumSize(QSize(400, 0));
        OnlineTuneDialog->setMaximumSize(QSize(400, 16777215));
        gridLayout = new QGridLayout(OnlineTuneDialog);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        tabWidget = new QTabWidget(OnlineTuneDialog);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        gridLayout_10 = new QGridLayout(tab);
        gridLayout_10->setObjectName(QString::fromUtf8("gridLayout_10"));
        groupBox_34 = new QGroupBox(tab);
        groupBox_34->setObjectName(QString::fromUtf8("groupBox_34"));
        groupBox_34->setMinimumSize(QSize(0, 65));
        groupBox_34->setMaximumSize(QSize(16777215, 62));
        pushButtonCameraState = new QPushButton(groupBox_34);
        pushButtonCameraState->setObjectName(QString::fromUtf8("pushButtonCameraState"));
        pushButtonCameraState->setGeometry(QRect(70, 33, 201, 23));

        gridLayout_10->addWidget(groupBox_34, 2, 0, 1, 1);

        groupBox_3 = new QGroupBox(tab);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setMinimumSize(QSize(0, 330));
        gridLayoutWidget = new QWidget(groupBox_3);
        gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(10, 30, 341, 270));
        gridLayout_2 = new QGridLayout(gridLayoutWidget);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        comboBoxCameraLinkMode = new QComboBox(gridLayoutWidget);
        comboBoxCameraLinkMode->addItem(QString());
        comboBoxCameraLinkMode->addItem(QString());
        comboBoxCameraLinkMode->addItem(QString());
        comboBoxCameraLinkMode->setObjectName(QString::fromUtf8("comboBoxCameraLinkMode"));

        gridLayout_2->addWidget(comboBoxCameraLinkMode, 2, 2, 1, 1);

        lineEditResolutionW = new QLineEdit(gridLayoutWidget);
        lineEditResolutionW->setObjectName(QString::fromUtf8("lineEditResolutionW"));

        gridLayout_2->addWidget(lineEditResolutionW, 0, 2, 1, 1);

        label_10 = new QLabel(gridLayoutWidget);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        gridLayout_2->addWidget(label_10, 0, 1, 1, 1);

        label_16 = new QLabel(gridLayoutWidget);
        label_16->setObjectName(QString::fromUtf8("label_16"));

        gridLayout_2->addWidget(label_16, 3, 0, 1, 1);

        btnReceive = new QPushButton(gridLayoutWidget);
        btnReceive->setObjectName(QString::fromUtf8("btnReceive"));

        gridLayout_2->addWidget(btnReceive, 6, 2, 1, 1);

        spinBoxImageBit = new QSpinBox(gridLayoutWidget);
        spinBoxImageBit->setObjectName(QString::fromUtf8("spinBoxImageBit"));
        spinBoxImageBit->setMinimum(8);
        spinBoxImageBit->setMaximum(16);
        spinBoxImageBit->setValue(16);

        gridLayout_2->addWidget(spinBoxImageBit, 3, 2, 1, 1);

        spinBoxImageTap = new QSpinBox(gridLayoutWidget);
        spinBoxImageTap->setObjectName(QString::fromUtf8("spinBoxImageTap"));
        spinBoxImageTap->setMinimum(1);
        spinBoxImageTap->setMaximum(10);
        spinBoxImageTap->setValue(1);

        gridLayout_2->addWidget(spinBoxImageTap, 4, 2, 1, 1);

        label_15 = new QLabel(gridLayoutWidget);
        label_15->setObjectName(QString::fromUtf8("label_15"));

        gridLayout_2->addWidget(label_15, 2, 0, 1, 1);

        label_14 = new QLabel(gridLayoutWidget);
        label_14->setObjectName(QString::fromUtf8("label_14"));

        gridLayout_2->addWidget(label_14, 1, 1, 1, 1);

        label_5 = new QLabel(gridLayoutWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout_2->addWidget(label_5, 0, 0, 1, 1);

        lineEditResolutionH = new QLineEdit(gridLayoutWidget);
        lineEditResolutionH->setObjectName(QString::fromUtf8("lineEditResolutionH"));

        gridLayout_2->addWidget(lineEditResolutionH, 1, 2, 1, 1);

        comboBoxImageFormat = new QComboBox(gridLayoutWidget);
        comboBoxImageFormat->addItem(QString());
        comboBoxImageFormat->setObjectName(QString::fromUtf8("comboBoxImageFormat"));

        gridLayout_2->addWidget(comboBoxImageFormat, 5, 2, 1, 1);

        label_17 = new QLabel(gridLayoutWidget);
        label_17->setObjectName(QString::fromUtf8("label_17"));

        gridLayout_2->addWidget(label_17, 4, 0, 1, 1);

        label_20 = new QLabel(gridLayoutWidget);
        label_20->setObjectName(QString::fromUtf8("label_20"));

        gridLayout_2->addWidget(label_20, 5, 0, 1, 1);

        btnSend = new QPushButton(gridLayoutWidget);
        btnSend->setObjectName(QString::fromUtf8("btnSend"));

        gridLayout_2->addWidget(btnSend, 6, 0, 1, 1);

        gridLayout_2->setColumnStretch(0, 5);

        gridLayout_10->addWidget(groupBox_3, 0, 0, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_10->addItem(verticalSpacer_2, 4, 0, 1, 1);

        tabWidget->addTab(tab, QString());

        gridLayout->addWidget(tabWidget, 0, 0, 1, 1);


        retranslateUi(OnlineTuneDialog);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(OnlineTuneDialog);
    } // setupUi

    void retranslateUi(QDialog *OnlineTuneDialog)
    {
        OnlineTuneDialog->setWindowTitle(QCoreApplication::translate("OnlineTuneDialog", "Online Tune Tool", nullptr));
        groupBox_34->setTitle(QCoreApplication::translate("OnlineTuneDialog", "\347\233\270\346\234\272\347\212\266\346\200\201", nullptr));
        pushButtonCameraState->setText(QCoreApplication::translate("OnlineTuneDialog", "\347\212\266\346\200\201\346\237\245\350\257\242", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("OnlineTuneDialog", "\347\233\270\346\234\272\345\217\202\346\225\260\351\205\215\347\275\256", nullptr));
        comboBoxCameraLinkMode->setItemText(0, QCoreApplication::translate("OnlineTuneDialog", "Base", nullptr));
        comboBoxCameraLinkMode->setItemText(1, QCoreApplication::translate("OnlineTuneDialog", "Medium", nullptr));
        comboBoxCameraLinkMode->setItemText(2, QCoreApplication::translate("OnlineTuneDialog", "Full", nullptr));

        lineEditResolutionW->setText(QCoreApplication::translate("OnlineTuneDialog", "4096", nullptr));
        label_10->setText(QCoreApplication::translate("OnlineTuneDialog", "\345\256\275", nullptr));
        label_16->setText(QCoreApplication::translate("OnlineTuneDialog", "\344\275\215\346\267\261", nullptr));
        btnReceive->setText(QCoreApplication::translate("OnlineTuneDialog", "\346\225\260\346\215\256\346\216\245\346\224\266", nullptr));
        spinBoxImageBit->setSuffix(QCoreApplication::translate("OnlineTuneDialog", "bit", nullptr));
        spinBoxImageTap->setSuffix(QCoreApplication::translate("OnlineTuneDialog", "tap", nullptr));
        label_15->setText(QCoreApplication::translate("OnlineTuneDialog", "CameraLink\345\267\245\344\275\234\346\250\241\345\274\217", nullptr));
        label_14->setText(QCoreApplication::translate("OnlineTuneDialog", "\351\253\230", nullptr));
        label_5->setText(QCoreApplication::translate("OnlineTuneDialog", "\345\210\206\350\276\250\347\216\207", nullptr));
        lineEditResolutionH->setText(QCoreApplication::translate("OnlineTuneDialog", "4096", nullptr));
        comboBoxImageFormat->setItemText(0, QCoreApplication::translate("OnlineTuneDialog", "RGB", nullptr));

        label_17->setText(QCoreApplication::translate("OnlineTuneDialog", "\351\200\232\351\201\223", nullptr));
        label_20->setText(QCoreApplication::translate("OnlineTuneDialog", "\345\233\276\345\203\217\346\225\260\346\215\256\346\240\274\345\274\217", nullptr));
        btnSend->setText(QCoreApplication::translate("OnlineTuneDialog", "\346\225\260\346\215\256\345\217\221\351\200\201", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("OnlineTuneDialog", "\346\215\225\350\216\267", nullptr));
    } // retranslateUi

};

namespace Ui {
    class OnlineTuneDialog: public Ui_OnlineTuneDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ONLINETUNEDIALOG_H
