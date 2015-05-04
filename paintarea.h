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

public:
  void panStart(QPointF p){ panStartP = p; }
  void panEnd(QPointF p);
  void Zoom(double _scale);

  virtual void translate(QPointF){}

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
  int maptype;
  QPointF panStartP;
  QRectF  geoRect;
  double  ZoomInOutScale;
};

#endif // PAINTAREA_H
