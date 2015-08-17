#include "udpmsgformat.h"
#include "ui_udpmsgformat.h"


udpmsgformat::udpmsgformat(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::udpmsgformat)
{
  ui->setupUi(this);
  QString qstr = "The Udp Message's format is like below: ";
  ui->textEdit->append(qstr);
  qstr = "'time:xxx,lon:xxx,lat:xxx,hgt:xxx,vel:xxx,az:xxx,status:xxx,lineIndex:xxx,pointIndex:xxx,"
      "flineIndex:xxx,fpointIndex:xxx,flon:xxx,flat:xxx,fhgt:xxx,aoy:xxx,distan:xxx'. ";
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

PatternInfo::PatternInfo(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::udpmsgformat)
{
    ui->setupUi(this);
    QString qstr("");
    qstr = QString::fromLocal8Bit("²¹ÅÄÄ£Ê½ ---- '#0' ");
    ui->textEdit->append(qstr);
    qstr = QString::fromLocal8Bit("Í£Ö¹²¹ÅÄ ---- '#1' ");
    ui->textEdit->append(qstr);
    qstr = QString::fromLocal8Bit("·µº½Ä£Ê½ ---- '#2' ");
    ui->textEdit->append(qstr);
    qstr = QString::fromLocal8Bit("Í£Ö¹·µº½ ---- '#3' ");
    ui->textEdit->append(qstr);
    qstr = QString::fromLocal8Bit("ÇëÇóãÐÖµ ---- '#4' ");
    ui->textEdit->append(qstr);
}

PatternInfo::~PatternInfo()
{
  delete ui;
}

void PatternInfo::on_close_clicked()
{
    this->close();
}
