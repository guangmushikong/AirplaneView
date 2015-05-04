#ifndef MYPOLYGON_H
#define MYPOLYGON_H

#include <QPolygonF>
#include <QPointF>

class mypolygon
{
public:
  mypolygon();
  const QPolygonF getCore(){ return _core; }
  void setCore(const QPolygonF& core){ _core = core; }
  void optimizeCoord(QPointF _trans, double _scale);

private:
  QPolygonF _core;
};

class MyPointF
{
public:
	MyPointF(qreal qx, qreal qy){ _core.setX(qx); _core.setY(qy); }
	MyPointF(const QPointF& p){ _core = p; }
	const QPointF& getCore(){ return _core; }
	void setCore(const QPointF& core){ _core = core; }
	void optimizeCoord(QPointF _trans, double _scale);

private:
	QPointF _core;
};

#endif // MYPOLYGON_H
