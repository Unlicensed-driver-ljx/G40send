/********************************************************************************
** Form generated from reading UI file 'QImageDisplayLabel.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QIMAGEDISPLAYLABEL_H
#define UI_QIMAGEDISPLAYLABEL_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>

QT_BEGIN_NAMESPACE

class Ui_QImageDisplayLabel
{
public:

    void setupUi(QLabel *QImageDisplayLabel)
    {
        if (QImageDisplayLabel->objectName().isEmpty())
            QImageDisplayLabel->setObjectName(QString::fromUtf8("QImageDisplayLabel"));
        QImageDisplayLabel->resize(1360, 1000);
        QSizePolicy sizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(QImageDisplayLabel->sizePolicy().hasHeightForWidth());
        QImageDisplayLabel->setSizePolicy(sizePolicy);
        QImageDisplayLabel->setFrameShape(QFrame::NoFrame);
        QImageDisplayLabel->setLineWidth(1);
        QImageDisplayLabel->setScaledContents(true);
        QImageDisplayLabel->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);

        retranslateUi(QImageDisplayLabel);

        QMetaObject::connectSlotsByName(QImageDisplayLabel);
    } // setupUi

    void retranslateUi(QLabel *QImageDisplayLabel)
    {
        QImageDisplayLabel->setWindowTitle(QCoreApplication::translate("QImageDisplayLabel", "QImageDisplayLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class QImageDisplayLabel: public Ui_QImageDisplayLabel {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QIMAGEDISPLAYLABEL_H
