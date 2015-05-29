#ifndef GEOSHAPEDATA_H
#define GEOSHAPEDATA_H

#include <set>
#include <list>
#include <QRectF>
#include <string>
#include "datadefine.h"
#include "drawobject.h"

using namespace std;


class GeoShapeData
{
  friend class drawObject;
  friend class drawAirplane;
  friend class drawAirPlaneTrail;
  friend class drawGP;
  friend class drawGeographicalPoint;
  friend class drawGeographicalPolyline;
  friend class drawGeographicalPolygon;
  friend class EagleEyeMap;
  friend class DetailedMap;
public:
  GeoShapeData();
  ~GeoShapeData();

public:
  static void registerGhtFile(string filePath);
  static void registerShape(void*& pVoid, shapeData::ShapeType t);
  static void releaseShape();
  static void registerGP(GuidancePointPtr& pPoint);
  static void releaseGPs();
  static void setAirPlane(QPointF p);
  static void setExposurePoint(QPointF p);
  //static bool getAirPlane(QPointF& p);
  static bool registerRecentFiles(std::string file);
  static void getGeoRect(QRectF& geoRect);

protected:
  static void recalcBoundingBox(QRectF& geoRect, void* pVoid, shapeData::ShapeType t);
  static void registerPoint(QRectF& rect, QPointF point);

protected:
  static QPointF currentAirplanePos;
  static list<shapeDataPtr> listShapeData;
  static list<GuidancePointPtr> listGPs;
  static std::set<std::string> setRecentFiles;
  //static std::list<QPointF> listAirplanes;
  static QVector<QPointF> vtrAirplaneTrail;
  static std::list<QPointF> listExposurePoint;
};

#endif // GEOSHAPEDATA_H
