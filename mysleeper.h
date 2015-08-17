#ifndef MYSLEEPER_H
#define MYSLEEPER_H

#include <QThread>

class MySleeper : public QThread
{
public:
    MySleeper();
    static void mysleep(unsigned long ms)
    {
        QThread::msleep(ms);
    }
};

#endif // MYSLEEPER_H
