#ifndef PAINTAREA_H
#define PAINTAREA_H

#include <QWidget>
#include <map>
#include <set>
#include <QLabel>
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
  static void setHeadingAngle(double _angle){ GeoShapeData::setHeadingAngle(_angle); }
  static void setGuidanceLine(QPointF beg, QPointF end){ GeoShapeData::setGuidanceLine(beg, end);}

public:
  void panStart(QPointF p){ panStartP = p; }
  void panEnd(QPointF p);
  void Zoom(double _scale, QPoint mouse);
  virtual void translate(QPointF){}
  virtual void move2point(QPointF); // Keep CCP in the viewport

public:
  virtual QPointF getWorldCoord(QPoint p){ return QPointF(.0, .0); }
  virtual QPoint  getPixelCoord(QPointF p){ return QPoint(0, 0); }

protected:
  void paintEvent(QPaintEvent* event);


signals:

protected:
  virtual double getDrawScale() = 0;
  virtual double getRealScale();
  virtual void setGeoCoordSys(QPainter& painter) = 0;
  virtual void paintLabelScale(QPainter& painter);

protected:
  std::map<shapeData::ShapeType, drawObject*> mapDrawObject;
  QLabel* pLabelScale;

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
