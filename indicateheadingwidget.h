#ifndef INDICATEHEADINGWIDGET_H
#define INDICATEHEADINGWIDGET_H

#include <QWidget>
#include <QLabel>

class IndicateHeadingWidget : public QWidget
{
  Q_OBJECT
public:
  explicit IndicateHeadingWidget(QWidget *parent = 0);
  ~IndicateHeadingWidget();

  void setAngle(int _lineAngle, int _realAngle);

signals:

public slots:

protected:
  void drawNeedle(int angle, QPainter& painter);
  void paintEvent(QPaintEvent* );

  int realAngle;
  int lineAngle;
  QLabel* pNorthLabel;

};

#endif // INDICATEHEADINGWIDGET_H
