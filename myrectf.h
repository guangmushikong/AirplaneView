#ifndef MYRECTF_H
#define MYRECTF_H

#include <QRectF>

class MyRectF
{
public:
  MyRectF(){}
  MyRectF(QPointF p1, QPointF p2);
  const QRectF getCore(){ return _core; }
  void setCore(QRectF& rect){ _core = rect; }
  void scaleVle(double _scale);
  void scaleSize(double _scale);
  void optimizeCoord(QPointF _trans, double _scale);
protected:
  QRectF _core;
};

#endif // MYRECTF_H
