#ifndef UDPSETTINGDIALOG_H
#define UDPSETTINGDIALOG_H

#include <QDialog>
#include <QLineEdit>

namespace Ui {
  class UdpSettingDialog;
}

class UdpSettingDialog : public QDialog
{
private:
  class myLineEdit : public QLineEdit
  {
  public:
    explicit myLineEdit(QWidget* parent = 0);
    ~myLineEdit();
  protected:
    virtual void mousePressEvent(QMouseEvent* event);
  };
  Q_OBJECT

public:
  explicit UdpSettingDialog(QWidget *parent = 0);
  ~UdpSettingDialog();
  uint getPort(){ return portNum; }

private slots:
  void on_buttonBox_accepted();

protected:
  virtual void paintEvent(QPaintEvent *);

private:
  Ui::UdpSettingDialog *ui;
  myLineEdit* pLE;
  int portNum;
  int lineFlg;

};



#endif // UDPSETTINGDIALOG_H
