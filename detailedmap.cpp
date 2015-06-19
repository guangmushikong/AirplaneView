#include "detailedmap.h"
#include <QPainter>
#include <QImage>
#include "coordtranslate.h"


DetailedMap::DetailedMap(QWidget* parent):PaintArea(parent)
{
  maptype = 1;
  drawObject* pDraw = new drawGP();
  mapDrawObject.insert(std::make_pair(shapeData::guidance, pDraw));

  //pDraw = new drawAirplane();
  //mapDrawObject.insert(std::make_pair(shapeData::airplane, pDraw));
  pDraw = new drawGuidanceLine();
  mapDrawObject.insert(std::make_pair(shapeData::guidanceline, pDraw));
}

DetailedMap::~DetailedMap()
{
}

double DetailedMap::getDrawScale()
{
  double xscale, yscale;
  if (geoRect.width() > 0)
  {
      xscale = ZoomInOutScale * 600.0 / geoRect.width();
  }
  if (geoRect.height() > 0)
  {
      yscale = ZoomInOutScale * 600.0 / geoRect.height();
  }

  double scale = (xscale < yscale ? xscale : yscale);

  return scale;
}

void DetailedMap::setGeoCoordSys(QPainter &painter)
{
  painter.setWindow(-300, 300, 600, -600);
}

void DetailedMap::translate(QPointF p)
{
  QPointF diffP = p;
  diffP /= PanScale;
  diffP /= getDrawScale();
  QPointF rf = geoRect.topLeft();
  rf.setX(rf.x() - diffP.x());
  rf.setY(rf.y() + diffP.y());
  geoRect.moveTopLeft(rf);
  this->update();
}

void DetailedMap::getGeoPixCoordFromOriginCoord(QPoint & p)
{
  p.setX(p.x()-300);
  p.setY(300-p.y());
}

QPointF DetailedMap::getWorldCoord(QPoint p)
{
  getGeoPixCoordFromOriginCoord(p);
  QPointF pixelP(p);
  CoordTranslate<QPointF> ct;
  ct.Pixel2World(geoRect, getDrawScale(), pixelP);

  return pixelP;
}
