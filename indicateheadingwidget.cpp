#include "indicateheadingwidget.h"
#include <QPainter>

#include <fstream>

#define PI 3.1415926

IndicateHeadingWidget::IndicateHeadingWidget(QWidget *parent) :
  QWidget(parent)
{
  setPalette(QPalette(QColor(0, 0, 0)));
  setAutoFillBackground(true);

  lineAngle = 0;
  realAngle = 0;
  pNorthLabel = new QLabel(this);
  pNorthLabel->setGeometry(85, 20, 30, 10);
  pNorthLabel->setText("North");
}

IndicateHeadingWidget::~IndicateHeadingWidget()
{
  delete pNorthLabel;
}

void IndicateHeadingWidget::setAngle(int _lineAngle, int _realAngle)
{
  lineAngle = _lineAngle;
  realAngle = _realAngle;
  update();
}

void IndicateHeadingWidget::paintEvent(QPaintEvent* ev)
{
  // draw circle
  QPainter painter(this);
  QPen pen;
  pen.setWidth(2);
  pen.setColor(Qt::white);
  painter.setPen(pen);
  painter.drawEllipse(0, 0, 200, 200);

  // draw scale
  painter.drawLine(QPoint(100, 0), QPoint(100, 5));
  painter.drawLine(QPoint(200, 100), QPoint(195, 100));
  painter.drawLine(QPoint(100, 200), QPoint(100, 195));
  painter.drawLine(QPoint(0, 100), QPoint(5, 100));

  // draw line angle
  painter.setPen(QPen(Qt::NoPen));
  painter.setBrush(QBrush(QColor(0, 0, 255)));
  drawNeedle(lineAngle, painter);
  painter.setBrush(QBrush(QColor(255, 0, 255)));
  drawNeedle(realAngle, painter);

}

void IndicateHeadingWidget::drawNeedle(int angle, QPainter& painter)
{
  if ( angle >=0 && angle <=360 )
  {
     //      p1
     //       /\
     //      /  \
     //     /    \
     //    p2     p3

    QPoint p1, p2, p3;
    int x, y, deltX, deltY;
    int lengthUnit = this->width() / 2;
    // get the coordinate of p1
    x = int( lengthUnit*(1 + sin(PI*angle/180.0)) );
    y = int( lengthUnit*(1 - cos(PI*angle/180.0)) );
    p1.setX(x);
    p1.setY(y);

    // p2
    int angle4P2 = angle - 90;
    if (0 > angle4P2)
      angle4P2 += 360;
    lengthUnit = this->width() / 16;
    deltX = int( lengthUnit*(sin(PI*angle4P2/180.0)));
    deltY = int( lengthUnit*(cos(PI*angle4P2/180.0)));
    p2.setX(100 + deltX);
    p2.setY(100 - deltY);

    // p3
    p3.setX(100 - deltX);
    p3.setY(100 + deltY);

    QPolygon polygon;
    polygon << p1 << p2 << p3;
    painter.drawPolygon(polygon);
  }
}
