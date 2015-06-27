#include "paintarea.h"
#include <QPainter>
#include "uiparamconfig.h"

#include <fstream>


PaintArea::PaintArea(QWidget *parent) :
  QWidget(parent)
{
  //setPalette(QPalette(QColor(128, 128, 128)));
  setPalette(QPalette(QColor(0, 0, 0)));
  setAutoFillBackground(true);

  // measure scale
  pLabelScale = new QLabel(this);

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

  delete pLabelScale;
}

void PaintArea::paintLabelScale(QPainter& painter)
{
//  int width = this->widthMM();
//  int height = this->heightMM();

//  std::ofstream outfile("c:/test1.txt");
//  outfile << width << " " << height << std::endl;
//  outfile << this->width() << " " << this->height() << std::endl;

  double length = this->width()*10/double(this->widthMM());

  // ///////draw line//////
  //
  //  1|__3__|2
  //
  /*/////////////////////*/
  painter.drawLine(30, 565, 30, 570); // 1
  painter.drawLine(30, 570, 30+length, 570); // 2
  painter.drawLine(30+length, 565, 30+length, 570); // 3

  // draw text
  if (getRealScale() > 0)
  {
    pLabelScale->setGeometry(30, 550, length*2, 10);
    QString text = QString::number(getRealScale());
    pLabelScale->setText(text);
  }
}

double PaintArea::getRealScale()
{
  double scale = -1.0;
  double xscale, yscale;
  if (geoRect.width() > 0 && geoRect.height() > 0)
  {
      xscale = geoRect.width()*36000 / this->widthMM() / ZoomInOutScale;
      yscale = geoRect.height()*36000 / this->heightMM() / ZoomInOutScale;

      scale = (xscale < yscale ? xscale : yscale);
  }

  return scale;
}

void PaintArea::paintEvent(QPaintEvent *event)
{
  QPainter painter(this);
  painter.setRenderHint(QPainter::Antialiasing, true);

  paintLabelScale(painter);

  if ( PlaneHeading == UIParamConfig::getViewDirection() )
  {
    if ( 1 == maptype )
    {
      painter.rotate(GeoShapeData::getHeadingAngle());
    }
  }

  setGeoCoordSys(painter);
  std::map<shapeData::ShapeType, drawObject*>::iterator it;
  for(it = mapDrawObject.begin(); it != mapDrawObject.end(); ++it)
  {
    if (it->first != shapeData::airplane)
    {
      drawObject* pDraw = it->second;
      pDraw->setGeoRect(geoRect);
      pDraw->setScale(getDrawScale());
      pDraw->draw(painter);
    }
  }

  it = mapDrawObject.find(shapeData::airplane);
  drawObject* pDraw = it->second;
  pDraw->setGeoRect(geoRect);
  pDraw->setScale(getDrawScale());
  pDraw->draw(painter);
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
  GeoShapeData::clearRecentFiles();
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

void PaintArea::move2point(QPointF p)
{
  //if (!geoRect.contains(p))
    geoRect.moveCenter(p);
}
