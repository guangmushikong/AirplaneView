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

void MyPointF::optimizeCoord(QPointF _trans, double _scale)
{
	_core -= _trans;
	_core *= _scale;
}
