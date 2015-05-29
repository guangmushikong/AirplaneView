#ifndef EAGLEEYEMAP_H
#define EAGLEEYEMAP_H
#include <QWidget>
#include "paintarea.h"

class EagleEyeMap : public PaintArea
{
  Q_OBJECT
public:
  explicit EagleEyeMap(QWidget* parent = 0);
  ~EagleEyeMap();

public:
  virtual void translate(QPointF);

protected:
  virtual double getDrawScale();
  virtual void setGeoCoordSys(QPainter& painter);
};

#endif // EAGLEEYEMAP_H
