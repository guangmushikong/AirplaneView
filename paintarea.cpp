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

  p = new drawGeographicalPolygon();
  mapDrawObject.insert(std::make_pair(shapeData::area, p));

  p = new drawGeographicalPolyline();
  mapDrawObject.insert(std::make_pair(shapeData::polyline, p));

  p = new drawAirPlaneTrail();
  mapDrawObject.insert(std::make_pair(shapeData::airplanetrail, p));

  p = new drawAirplane();
  mapDrawObject.insert(std::make_pair(shapeData::airplane, p));

  ZoomInOutScale = 1.0;
  bZoom = false;
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
  setGeoCoordSys(painter);
  std::map<shapeData::ShapeType, drawObject*>::iterator it;
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
  ZoomInOutScale = 1.0;
}

void PaintArea::releaseShapes()
{
  GeoShapeData::releaseShape();
  GeoShapeData::releaseGPs();
  geoRect.setWidth(.0);
  geoRect.setHeight(.0);
  ZoomInOutScale = 1.0;
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
  //QPointF transP = (panStartP-p);
  QPointF transP = (p-panStartP);
  translate(transP);
}

void PaintArea::Zoom(double _scale, QPoint mouse)
{
  if (_scale > 0)
  {
    bZoom = true;
    // mousePos = mouse;
    ZoomInOutScale *= _scale;
    this->update();
  }
}
