/********************************************************************************
** Form generated from reading UI file 'qtracker.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTRACKER_H
#define UI_QTRACKER_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QWidget>
#include "UI/QImageDisplayLabel.h"

QT_BEGIN_NAMESPACE

class Ui_QTracker
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QImageDisplayLabel *labelImageDisplay;

    void setupUi(QMainWindow *QTracker)
    {
        if (QTracker->objectName().isEmpty())
            QTracker->setObjectName(QString::fromUtf8("QTracker"));
        QTracker->resize(151, 100);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(QTracker->sizePolicy().hasHeightForWidth());
        QTracker->setSizePolicy(sizePolicy);
        QTracker->setMaximumSize(QSize(16777215, 16777215));
        QTracker->setCursor(QCursor(Qt::ArrowCursor));
        QTracker->setAutoFillBackground(false);
        centralWidget = new QWidget(QTracker);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        centralWidget->setAutoFillBackground(false);
        centralWidget->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        labelImageDisplay = new QImageDisplayLabel(centralWidget);
        labelImageDisplay->setObjectName(QString::fromUtf8("labelImageDisplay"));
        QSizePolicy sizePolicy1(QSizePolicy::Ignored, QSizePolicy::Ignored);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(labelImageDisplay->sizePolicy().hasHeightForWidth());
        labelImageDisplay->setSizePolicy(sizePolicy1);
        labelImageDisplay->setMinimumSize(QSize(1000, 1000));
        labelImageDisplay->setMaximumSize(QSize(1000, 1000));
        QFont font;
        font.setPointSize(14);
        labelImageDisplay->setFont(font);
        labelImageDisplay->setAutoFillBackground(false);
        labelImageDisplay->setStyleSheet(QString::fromUtf8("background-color: rgb(85, 170, 255);"));
        labelImageDisplay->setFrameShape(QFrame::NoFrame);
        labelImageDisplay->setLineWidth(1);
        labelImageDisplay->setScaledContents(true);
        labelImageDisplay->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(labelImageDisplay, 0, 0, 1, 1);

        QTracker->setCentralWidget(centralWidget);

        retranslateUi(QTracker);

        QMetaObject::connectSlotsByName(QTracker);
    } // setupUi

    void retranslateUi(QMainWindow *QTracker)
    {
        QTracker->setWindowTitle(QCoreApplication::translate("QTracker", "HF-4040FSI-CIOMP", nullptr));
        labelImageDisplay->setText(QCoreApplication::translate("QTracker", "\347\233\270\346\234\272\345\210\235\345\247\213\345\214\226\344\270\255......", nullptr));
    } // retranslateUi

};

namespace Ui {
    class QTracker: public Ui_QTracker {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTRACKER_H
