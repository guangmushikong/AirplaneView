#include "mypolygon.h"

mypolygon::mypolygon()
{
  _core = QPolygonF();
}

void mypolygon::optimizeCoord(QPointF _trans, double _scale)
{
  for(QPolygonF::iterator it = _core.begin();
      it != _core.end(); ++it)
  {
      it->operator -=(_trans);
      it->operator *=(_scale);
  }
}

MyLine::MyLine()
{}

void MyLine::optimizeCoord(QPointF _trans, double _scale)
{
    QPointF p1 = _core.p1();
    p1 -= _trans;
    p1 *= _scale;

    QPointF p2 = _core.p2();
    p2 -= _trans;
    p2 *= _scale;

    _core.setP1(p1);
    _core.setP2(p2);
}

void MyPointF::optimizeCoord(QPointF _trans, double _scale)
{
	_core -= _trans;
	_core *= _scale;
}
