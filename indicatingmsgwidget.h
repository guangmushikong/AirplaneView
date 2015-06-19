#ifndef INDICATINGMSGWIDGET_H
#define INDICATINGMSGWIDGET_H

#include <QWidget>
#include <QSlider>
#include <QLabel>


class MySlider : public QSlider
{
  Q_OBJECT
public:
  MySlider(QWidget* parent = 0):QSlider(parent)
  {
    //QFont font;
    //font.setPointSize(16);
    //pPlaneMsgLabel->setFont(font);
    QPalette palette;
    palette.setColor(QPalette::WindowText, Qt::white);
  }
  ~MySlider()
  {
  }

protected:

};

class IndicatingMsgWidget : public QWidget
{
  Q_OBJECT
public:
  explicit IndicatingMsgWidget(QWidget *parent = 0);
  ~IndicatingMsgWidget();

public:
  void setHeight(int vle);
  void setHeightRange(int min, int max);

signals:

public slots:

protected:
  /*MySlider**/
  QSlider* pIndicateHeight;

  QLabel* pMinLabel;
  QLabel* pMaxLabel;
  QLabel* pMidLabel;

};

#endif // INDICATINGMSGWIDGET_H
