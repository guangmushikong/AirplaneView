#include "paintarea.h"
#include <QPainter>

PaintArea::PaintArea(QWidget *parent) :
  QWidget(parent)
{
  //setPalette(QPalette(Qt::white));
  setPalette(QPalette(QColor(128, 128, 128)));
  setAutoFillBackground(true);

  // initialize the drawobject
  //QPainter painter(this);
  //drawObject::setGeoCoordSys(painter);
  drawObject* p;
  p = new drawGeographicalPoint();
  mapDrawObject.insert(std::make_pair(shapeData::point, p));

  p = new drawGeographicalLine();
  mapDrawObject.insert(std::make_pair(shapeData::line, p));

  p = new drawGeographicalPolygon();
  mapDrawObject.insert(std::make_pair(shapeData::area, p));

  p = new drawGeographicalPolyline();
  mapDrawObject.insert(std::make_pair(shapeData::polyline, p));

  p = new drawAirplane();
  mapDrawObject.insert(std::make_pair(shapeData::airplane, p));

  ZoomInOutScale = 1.0;
}

PaintArea::~PaintArea()
{
  std::map<shapeData::ShapeType, drawObject*>::iterator it;
  for(it = mapDrawObject.begin(); it != mapDrawObject.end(); ++it)
  {
      delete (it->second);
  }

  GeoShapeData::releaseShape();
  GeoShapeData::releaseGPs();
}

void PaintArea::paintEvent(QPaintEvent *event)
{
  QPainter painter(this);
  std::map<shapeData::ShapeType, drawObject*>::iterator it;
  //GeoShapeData::getGeoRect(geoRect);
  for(it = mapDrawObject.begin(); it != mapDrawObject.end(); ++it)
  {
    drawObject* pDraw = it->second;
    pDraw->setGeoRect(geoRect);
    pDraw->setScale(getDrawScale());
    pDraw->draw(painter);
  }
}

void PaintArea::registerShape(void *pVoid, shapeData::ShapeType type, int nNum)
{
  //calGeoRect(pVoid, type);
  GeoShapeData::registerShape(pVoid, type);
  GeoShapeData::getGeoRect(geoRect);
}

void PaintArea::releaseShapes()
{
  GeoShapeData::releaseShape();
  geoRect.setWidth(.0);
  geoRect.setHeight(.0);
}

void PaintArea::registerGhtFile(std::string filePath)
{
  if ( GeoShapeData::registerRecentFiles(filePath) )
  {
      GeoShapeData::registerGhtFile(filePath);
  }
  GeoShapeData::getGeoRect(geoRect);
}

void PaintArea::panEnd(QPointF p)
{
  QPointF transP = (panStartP-p);
  translate(transP);
}

void PaintArea::Zoom(double _scale)
{
  if (_scale > 0)
  {
    ZoomInOutScale *= _scale;
    this->update();
  }
}
