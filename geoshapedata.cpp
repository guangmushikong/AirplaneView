#include "geoshapedata.h"
#include <QLineF>
#include <QPolygonF>
#include <sstream>
#include <fstream>

list<shapeDataPtr> GeoShapeData::listShapeData;
list<GuidancePointPtr> GeoShapeData::listGPs;
set<string> GeoShapeData::setRecentFiles;
//QRectF GeoShapeData::geoRect;
QPointF GeoShapeData::currentAirplanePos;
//list<QPointF> GeoShapeData::listAirplanes;
QVector<QPointF> GeoShapeData::vtrAirplaneTrail;
list<QPointF> GeoShapeData::listExposurePoint;
double GeoShapeData::headingAngle;
QLineF GeoShapeData::guidanceLine;

GeoShapeData::GeoShapeData()
{
}

GeoShapeData::~GeoShapeData()
{}

void GeoShapeData::registerShape(void* &pVoid, shapeData::ShapeType t)
{
  //recalcBoundingBox(pVoid, t);
  // save the data
  shapeData* pData = new shapeData(pVoid, t);
  listShapeData.push_back(pData);
}

void GeoShapeData::releaseShape()
{
  std::list<shapeData*>::iterator it = listShapeData.begin();
  std::list<shapeData*>::iterator itEnd = listShapeData.end();
  for (; it != itEnd; it++)
  {
    delete (*it);
  }
  listShapeData.clear();
  //geoRect.setHeight(.0);
  //geoRect.setWidth(.0);
}

void GeoShapeData::registerGP(GuidancePointPtr& pPoint)
{
  listGPs.push_back(pPoint);
}

void GeoShapeData::releaseGPs()
{
  for(std::list<GuidancePoint*>::iterator it = listGPs.begin();
      it != listGPs.end(); ++it)
  {
      delete (*it);
  }
  listGPs.clear();

  vtrAirplaneTrail.clear();
}

void GeoShapeData::setAirPlane(QPointF p)
{
  //airPlane = p;
  //listAirplanes.push_back(p);
  vtrAirplaneTrail.push_back(p);
  currentAirplanePos = p;
}

void GeoShapeData::setExposurePoint(QPointF p)
{
  listExposurePoint.push_back(p);
}

//bool GeoShapeData::getAirPlane(QPointF& p)
//{
//	bool bRlt = false;
//	if (vtrAirplanes.size()>0)
//	{
//		p = vtrAirplanes.at(vtrAirplanes.size()-1);
//		bRlt = true;
//	}
//
//	return bRlt;
//}

void GeoShapeData::registerPoint(QRectF &rect, QPointF point)
{
  qreal x1, y1, x2, y2;
  rect.getCoords(&x1, &y1, &x2, &y2);

  if(x1 > point.x())
          x1 = point.x();
  else if(x2 < point.x())
          x2 = point.x();

  if(y1 > point.y())
          y1 = point.y();
  else if(y2 < point.y())
          y2 = point.y();

  rect.setCoords(x1, y1, x2, y2);
}

void GeoShapeData::recalcBoundingBox(QRectF& geoRect,
                                     void* pVoid,
                                     shapeData::ShapeType t)
{
  // recalculate Bounding box
  if(shapeData::point == t)
  {
    QPointF* pPoint = (QPointF*)pVoid;
    if(!geoRect.contains(*pPoint))
    {
      registerPoint(geoRect, *pPoint);
    }
  }
  else if(shapeData::line == t)
  {
    QLineF* pLine = (QLineF*)pVoid;
    QPointF p1 = pLine->p1();
    QPointF p2 = pLine->p2();
    if(!geoRect.contains(p1)){ registerPoint(geoRect, p1);}
    if(!geoRect.contains(p2)){ registerPoint(geoRect, p2);}
  }
  else if(shapeData::area == t || shapeData::polyline == t)
  {
    QPolygonF* pPolygon = (QPolygonF*)pVoid;
    QRectF rect = pPolygon->boundingRect();
    if(!geoRect.contains(rect)){ geoRect = geoRect | rect;}
  }
}

void GeoShapeData::registerGhtFile(string filePath)
{
  if(filePath.empty())
      return;

  std::istringstream iss;
  std::string line;
  std::string pointType;
  double dCoordX, dCoordY, dCoordZ;
  int lineNum, PointNum, type;
  GuidancePoint* pGP = 0;
  void* pVoid = 0;
  QVector<QPointF> vtrPoints;

  std::ifstream infile(filePath);
  if(!infile.is_open())
  {
      return;
  }

  while (getline(infile, line))
  {
    iss.clear();

    if(std::string::npos != line.find("AIRPORT"))
    {
        continue;
    }
    else if(std::string::npos != line.find("-"))
    {
      line.replace(line.find("-"), 1, " ");
      iss.str(line);

      if(std::string::npos != line.find("A1"))
      {
          iss >> lineNum >> pointType >> dCoordX >> dCoordY >> dCoordZ >> type;
          pGP = new GuidancePoint(GuidancePoint::A1Type,
                                  QPointF(dCoordY, dCoordX),
                                  lineNum);
      }
      else if(std::string::npos != line.find("A2"))
      {
          iss >> lineNum >> pointType >> dCoordX >> dCoordY >> dCoordZ >> type;
          pGP = new GuidancePoint(GuidancePoint::A2Type,
                                  QPointF(dCoordY, dCoordX),
                                  lineNum);
      }
      else if(std::string::npos != line.find("B1"))
      {
          iss >> lineNum >> pointType >> dCoordX >> dCoordY >> dCoordZ >> type;
          pGP = new GuidancePoint(GuidancePoint::B1Type,
                                  QPointF(dCoordY, dCoordX),
                                  lineNum);
      }
      else if(std::string::npos != line.find("B2"))
      {
          iss >> lineNum >> pointType >> dCoordX >> dCoordY >> dCoordZ >> type;
          pGP = new GuidancePoint(GuidancePoint::B2Type,
                                  QPointF(dCoordY, dCoordX),
                                  lineNum);
      }
      else
      {
          iss >> lineNum >> PointNum >> dCoordX >> dCoordY >> dCoordZ >> type;
          pGP = new GuidancePoint(GuidancePoint::Normal,
                                  QPointF(dCoordY, dCoordX),
                                  lineNum,
                                  PointNum);
      }
      vtrPoints.push_back(QPointF(dCoordY, dCoordX));
    }
    else
      continue;

    registerGP(pGP);

  }
  infile.close();
  pVoid = new QPolygonF(vtrPoints);
  registerShape(pVoid, shapeData::polyline);
  //recalcBoundingBox(geoRect, pVoid, shapeData::polyline);
}

bool GeoShapeData::registerRecentFiles(std::string file)
{
	bool bRlt = false;
	if (setRecentFiles.end() == setRecentFiles.find(file))
	{
		setRecentFiles.insert(file);
		bRlt = true;
	}

	return bRlt;
}

void GeoShapeData::getGeoRect(QRectF& geoRect)
{
	list<shapeDataPtr>::iterator it;
	for (it = listShapeData.begin(); it != listShapeData.end(); ++it)
	{
		shapeDataPtr ptr = *it;
		recalcBoundingBox(geoRect, ptr->pVoid, ptr->type);
	}
}

void GeoShapeData::setHeadingAngle(double _angle)
{
  headingAngle = _angle;
}

void GeoShapeData::clearRecentFiles()
{
  setRecentFiles.clear();
}

void GeoShapeData::setGuidanceLine(QPointF beg, QPointF end)
{
  guidanceLine.setLine(beg.x(), beg.y(), end.x(), end.y());
}
