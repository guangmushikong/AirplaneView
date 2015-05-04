#ifndef UDPMSGFORMAT_H
#define UDPMSGFORMAT_H

#include <QDialog>

namespace Ui {
  class udpmsgformat;
}

class udpmsgformat : public QDialog
{
  Q_OBJECT

public:
  explicit udpmsgformat(QWidget *parent = 0);
  ~udpmsgformat();

private slots:
  void on_close_clicked();

private:
  Ui::udpmsgformat *ui;
};

#endif // UDPMSGFORMAT_H
