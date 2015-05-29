#ifndef PAINTAREA_H
#define PAINTAREA_H

#include <QWidget>
#include <map>
#include <set>
#include "drawobject.h"
#include "geoshapedata.h"



class PaintArea : public QWidget
{
  Q_OBJECT
public:
  explicit PaintArea(QWidget *parent = 0);
  ~PaintArea();
  void registerShape(void* pVoid, shapeData::ShapeType type, int nNum=1);
  void registerGhtFile(std::string filePath);
  void releaseShapes();
  static void setAirPlane(QPointF pf){ GeoShapeData::setAirPlane(pf); }
  static void setExposurePoint(QPointF pf){ GeoShapeData::setExposurePoint(pf); }

public:
  void panStart(QPointF p){ panStartP = p; }
  void panEnd(QPointF p);
  void Zoom(double _scale, QPoint mouse);
  virtual void translate(QPointF){}

public:
  virtual QPointF getWorldCoord(QPoint p){ return QPointF(.0, .0); }
  virtual QPoint  getPixelCoord(QPointF p){ return QPoint(0, 0); }

protected:
  void paintEvent(QPaintEvent* event);


signals:

protected:
  virtual double getDrawScale() = 0;
  virtual void setGeoCoordSys(QPainter& painter) = 0;

protected:
  std::map<shapeData::ShapeType, drawObject*> mapDrawObject;
  //std::set<std::string> setRecentFiles;


protected:
  /*
   * maptype = 0 -- EagleEyeMap
   * maptype = 1 -- DetailedMap
  */
  int      maptype;
  QPointF  panStartP;
  QRectF   geoRect;
  QPoint   mousePos; // used to zoom
  double   ZoomInOutScale;
  bool     bZoom;

};

#endif // PAINTAREA_H
