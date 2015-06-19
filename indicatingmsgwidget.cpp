#include "indicatingmsgwidget.h"

IndicatingMsgWidget::IndicatingMsgWidget(QWidget *parent) :
  QWidget(parent)
{
  setPalette(QPalette(QColor(0, 0, 0)));
  setAutoFillBackground(true);

  pIndicateHeight = new MySlider(this);
  pIndicateHeight->setEnabled(false);
  pIndicateHeight->setGeometry(30, 0, 20, 200);
  pIndicateHeight->setTickPosition(QSlider::TicksLeft);
  pIndicateHeight->setTickInterval(50);
  pIndicateHeight->setRange(500, 1500);

  pMinLabel = new QLabel(this);
  pMinLabel->setGeometry(0, 190, 20, 10);
  pMinLabel->setText("500");
  pMaxLabel = new QLabel(this);
  pMaxLabel->setGeometry(0, 0, 20, 10);
  pMaxLabel->setText("1500");
  pMidLabel = new QLabel(this);
  pMidLabel->setGeometry(0, 100, 20, 10);
  pMidLabel->setText("1000");
}

IndicatingMsgWidget::~IndicatingMsgWidget()
{
  delete pMinLabel;
  delete pMaxLabel;
  delete pMidLabel;
  delete pIndicateHeight;
}

void IndicatingMsgWidget::setHeightRange(int min, int max)
{
  pIndicateHeight->setRange(min, max);
}

void IndicatingMsgWidget::setHeight(int vle)
{
  pIndicateHeight->setValue(vle);
  update();
}
