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

  //test
  //void drawline();
  virtual void translate(QPointF p);

protected:
  virtual double getDrawScale();
  virtual void setGeoCoordSys(QPainter& painter);
};

#endif // DETAILEDMAP_H
