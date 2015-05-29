#include "udpmsgformat.h"
#include "ui_udpmsgformat.h"

udpmsgformat::udpmsgformat(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::udpmsgformat)
{
  ui->setupUi(this);
  QString qstr = "The Udp Message's format is like below: ";
  ui->textEdit->append(qstr);
  qstr = "'time:xxx,lon:xxx,lat:xxx,hgt:xxx,vel:xxx,az:xxx,status:xxx,lineIndex:xxx,pointIndex:xxx'. ";
  ui->textEdit->append(qstr);
  qstr = "And the program could cope with the length of prefix(such as time/lon).";
  ui->textEdit->append(qstr);
}

udpmsgformat::~udpmsgformat()
{
  delete ui;
}

void udpmsgformat::on_close_clicked()
{
    this->close();
}
