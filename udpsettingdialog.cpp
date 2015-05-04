#include "udpsettingdialog.h"
#include "ui_udpsettingdialog.h"
#include <QMouseEvent>
#include <fstream>

UdpSettingDialog::UdpSettingDialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::UdpSettingDialog)
{
  ui->setupUi(this);
  pLE = new myLineEdit(this);
  pLE->setGeometry(130, 30, 100, 20);
  portNum = 7001;
  lineFlg = 0;
}

UdpSettingDialog::~UdpSettingDialog()
{
  delete ui;
}

void UdpSettingDialog::on_buttonBox_accepted()
{
    portNum = pLE->text().toUInt();
}

void UdpSettingDialog::paintEvent(QPaintEvent *)
{
  if (0 == lineFlg)
  {
      pLE->setText(QString::number(portNum));
      ++lineFlg;
  }
}

UdpSettingDialog::myLineEdit::myLineEdit(QWidget *parent):QLineEdit(parent)
{}

UdpSettingDialog::myLineEdit::~myLineEdit()
{}

void UdpSettingDialog::myLineEdit::mousePressEvent(QMouseEvent *event)
{
  if (Qt::LeftButton == event->button())
  {
      this->clear();
  }
}
