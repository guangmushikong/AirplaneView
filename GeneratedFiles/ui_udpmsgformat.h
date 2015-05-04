/********************************************************************************
** Form generated from reading UI file 'udpmsgformat.ui'
**
** Created by: Qt User Interface Compiler version 5.2.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_UDPMSGFORMAT_H
#define UI_UDPMSGFORMAT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>

QT_BEGIN_NAMESPACE

class Ui_udpmsgformat
{
public:
    QPushButton *close;
    QTextEdit *textEdit;

    void setupUi(QDialog *udpmsgformat)
    {
        if (udpmsgformat->objectName().isEmpty())
            udpmsgformat->setObjectName(QStringLiteral("udpmsgformat"));
        udpmsgformat->resize(431, 217);
        close = new QPushButton(udpmsgformat);
        close->setObjectName(QStringLiteral("close"));
        close->setGeometry(QRect(340, 170, 75, 23));
        textEdit = new QTextEdit(udpmsgformat);
        textEdit->setObjectName(QStringLiteral("textEdit"));
        textEdit->setGeometry(QRect(20, 40, 391, 111));

        retranslateUi(udpmsgformat);

        QMetaObject::connectSlotsByName(udpmsgformat);
    } // setupUi

    void retranslateUi(QDialog *udpmsgformat)
    {
        udpmsgformat->setWindowTitle(QApplication::translate("udpmsgformat", "Udp Message Format", 0));
        close->setText(QApplication::translate("udpmsgformat", "Close", 0));
    } // retranslateUi

};

namespace Ui {
    class udpmsgformat: public Ui_udpmsgformat {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UDPMSGFORMAT_H
