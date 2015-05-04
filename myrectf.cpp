#include "myrectf.h"

MyRectF::MyRectF(QPointF p1, QPointF p2)
{
  _core.setTopLeft(p1);
  _core.setBottomRight(p2);
}

void MyRectF::scaleVle(double _scale)
{
  qreal x1, y1, x2, y2;
  _core.getCoords(&x1, &y1, &x2, &y2);
  _core.setCoords(x1*_scale,
                  y1*_scale,
                  x2*_scale,
                  y2*_scale);
}

void MyRectF::scaleSize(double _scale)
{
	_core.setWidth(_core.width()*_scale);
	_core.setHeight(_core.height()*_scale);
}

void MyRectF::optimizeCoord(QPointF _trans, double _scale)
{  qreal x1, y1, x2, y2;
	_core.getCoords(&x1, &y1, &x2, &y2);
	_core.setCoords((x1-_trans.x())*_scale,
		(y1-_trans.y())*_scale,
		(x2-_trans.x())*_scale,
		(y2-_trans.y())*_scale);
}
