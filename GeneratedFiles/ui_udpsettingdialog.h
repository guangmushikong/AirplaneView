/********************************************************************************
** Form generated from reading UI file 'udpsettingdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.2.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_UDPSETTINGDIALOG_H
#define UI_UDPSETTINGDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>

QT_BEGIN_NAMESPACE

class Ui_UdpSettingDialog
{
public:
    QDialogButtonBox *buttonBox;
    QLabel *label;

    void setupUi(QDialog *UdpSettingDialog)
    {
        if (UdpSettingDialog->objectName().isEmpty())
            UdpSettingDialog->setObjectName(QStringLiteral("UdpSettingDialog"));
        UdpSettingDialog->resize(400, 152);
        buttonBox = new QDialogButtonBox(UdpSettingDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(290, 20, 81, 241));
        buttonBox->setOrientation(Qt::Vertical);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        label = new QLabel(UdpSettingDialog);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(50, 30, 163, 20));

        retranslateUi(UdpSettingDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), UdpSettingDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), UdpSettingDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(UdpSettingDialog);
    } // setupUi

    void retranslateUi(QDialog *UdpSettingDialog)
    {
        UdpSettingDialog->setWindowTitle(QApplication::translate("UdpSettingDialog", "Reset Udp Socket", 0));
        label->setText(QApplication::translate("UdpSettingDialog", "Reset Port", 0));
    } // retranslateUi

};

namespace Ui {
    class UdpSettingDialog: public Ui_UdpSettingDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UDPSETTINGDIALOG_H
