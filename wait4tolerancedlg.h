#ifndef WAIT4TOLERANCEDLG_H
#define WAIT4TOLERANCEDLG_H

#include <QDialog>
#include <QLabel>

class Wait4ToleranceDlg : public QDialog
{
    Q_OBJECT
public:
    explicit Wait4ToleranceDlg(QWidget *parent = 0);
    ~Wait4ToleranceDlg();

signals:

public slots:

private:
    QLabel* pTextLabel;

};

#endif // WAIT4TOLERANCEDLG_H
