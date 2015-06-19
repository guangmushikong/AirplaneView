#ifndef DETAILEDMAP_H
#define DETAILEDMAP_H
#include <QWidget>
#include "paintarea.h"

#define PanScale 1


class DetailedMap : public PaintArea
{
  Q_OBJECT
public:
  explicit DetailedMap(QWidget* parent = 0);
  ~DetailedMap();

  virtual void translate(QPointF p);
  //virtual void move2point(QPointF p);

public:
  QPointF getWorldCoord(QPoint p);

protected:
  virtual double getDrawScale();
  virtual void setGeoCoordSys(QPainter& painter);
  void getGeoPixCoordFromOriginCoord(QPoint&);
};

#endif // DETAILEDMAP_H
