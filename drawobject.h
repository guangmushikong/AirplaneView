#ifndef DRAWOBJECT_H
#define DRAWOBJECT_H

#include <QString>
#include <QRect>
#include <QMatrix>
#include <list>
#include "datadefine.h"

class QPainter;

class drawObject
{
public:
  virtual void draw(QPainter& painter) = 0;
  void setScale(double _scale){ scale = _scale; }
  void setGeoRect(QRectF _rect){ geoRect = _rect; }

protected:
  double scale;
  QRectF geoRect;
};

// exposure point and CCP
class drawAirplane : public drawObject
{
public:
  void draw(QPainter &painter);
};

// guidance point
class drawGP : public drawObject
{
public:
  void draw(QPainter &painter);
};

//
class drawGeographicalPoint : public drawObject
{
public:
  void draw(QPainter& painter);
};

class drawAirPlaneTrail : public drawObject
{
public:
  void draw(QPainter &painter);
};

class drawGeographicalPolygon : public drawObject
{
public:
  void draw(QPainter& painter);
};

class drawGeographicalPolyline : public drawObject
{
public:
    void draw(QPainter &painter);
};

class drawGuidanceLine : public drawObject
{
public:
  void draw(QPainter &painter);
};

#endif // DRAWOBJECT_H
