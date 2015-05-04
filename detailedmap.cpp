#include "detailedmap.h"
#include <QPainter>
#include <QImage>

//#include "drawobject.h"

DetailedMap::DetailedMap(QWidget* parent):PaintArea(parent)
{
  maptype = 1;
  drawObject* pDraw = new drawGP();
  mapDrawObject.insert(std::make_pair(shapeData::guidance, pDraw));
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
}

void DetailedMap::translate(QPointF p)
{
  QPointF diffP = p;
  diffP /= PanScale;
  diffP /= getDrawScale();
  QPointF rf = geoRect.topLeft();
  rf += diffP;
  geoRect.moveTopLeft(rf);
  this->update();
}
