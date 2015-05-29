#include "eagleeyemap.h"
#include "geoshapedata.h"
#include <QPainter>

EagleEyeMap::EagleEyeMap(QWidget* parent) : PaintArea(parent)
{
  maptype = 0;
}

EagleEyeMap::~EagleEyeMap()
{

}

void EagleEyeMap::translate(QPointF)
{

}

double EagleEyeMap::getDrawScale()
{
  double xscale, yscale;
  if (geoRect.width() > 0)
  {
    xscale = 200.0 / geoRect.width();
  }
  if (geoRect.height() > 0)
  {
    yscale = 200.0 / geoRect.height();
  }

  double scale = (xscale < yscale ? xscale : yscale);

  return scale;
}

void EagleEyeMap::setGeoCoordSys(QPainter &painter)
{
  painter.setWindow(-100, 100, 200, -200);
}
