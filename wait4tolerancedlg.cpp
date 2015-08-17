#include "wait4tolerancedlg.h"
#include <QApplication>
#include <QDesktopWidget>

Wait4ToleranceDlg::Wait4ToleranceDlg(QWidget *parent) :
    QDialog(parent)
{
    this->setFixedSize(300, 150);
    int sgWidth  = QApplication::desktop()->width();
    int sgHeight = QApplication::desktop()->height();
    this->move((sgWidth-this->width())/2,
               (sgHeight-this->height())/2);
    pTextLabel = new QLabel(this);
    pTextLabel->setGeometry(20, 50, 280, 20);
    pTextLabel->setText(QString("Waiting for distance and height tolerance..."));
}

Wait4ToleranceDlg::~Wait4ToleranceDlg()
{
    delete pTextLabel;
}
