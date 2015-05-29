#include "drawobject.h"
#include <qdebug.h>
#include <QPainter>
#include <fstream>
#include "myrectf.h"
#include "mypolygon.h"
#include "geoshapedata.h"


//void drawObject::setGeoCoordSys(QPainter &painter)
//{
//  // view coordinate system and geographical coordinate system
//  //painter.setWindow(0, 400, 400, -400);
//  painter.setWindow(-200, 200, 400, -400);
//  QImage img("c:/airPlane.jpg");
//  painter.drawImage(0, 0, img);
//  painter.drawLine(QPoint(0, 0), QPoint(100, 100));
//  painter.drawLine(QPoint(0, 0), QPoint(100, -100));
//}

//void drawObject::translate(QPainter &painter)
//{
//  QPointF pf  = GeoShapeData::geoRect.topLeft();
//  pf += QPointF(0.5, 0.5);
//  GeoShapeData::geoRect.moveTopLeft(pf);
//}

void drawAirplane::draw(QPainter &painter)
{
  QBrush brush(QColor(255, 255, 255));
  painter.setBrush(brush);
  painter.setPen(Qt::NoPen);
  QPointF pf;
  list<QPointF>::iterator it;
  for (it  = GeoShapeData::listExposurePoint.begin();
       it != GeoShapeData::listExposurePoint.end(); ++it)
  {
    pf = *it;
    pf -= geoRect.center();
    pf *= scale;
    painter.drawEllipse(pf, 3, 3);
  }

  // CCP
  if (GeoShapeData::currentAirplanePos != QPointF(.0, .0))
  {
    brush.setColor(QColor(255, 0, 0));
    painter.setBrush(brush);
    pf = GeoShapeData::currentAirplanePos;
    pf -= geoRect.center();
    pf *= scale;
    painter.drawEllipse(pf, 3, 3);
  }
}

void drawGP::draw(QPainter &painter)
{
  QBrush brush(QColor(0, 255, 0));
  painter.setBrush(brush);
  painter.setPen(Qt::NoPen);
  std::list<GuidancePointPtr>::iterator it;
  for (it  = GeoShapeData::listGPs.begin();
       it != GeoShapeData::listGPs.end();
       it ++)
  {
      GuidancePointPtr ptr = *it;
      QPointF pf(ptr->point);
      //pf -= geoRect.topLeft();
      pf -= geoRect.center();
      pf *= scale;
      painter.drawEllipse(pf, 3, 3);
  }
}

void drawGeographicalPoint::draw(QPainter &painter)
{
  // the key of drawing geographical coordinate
  // is the translation of coordinate system
  QBrush PlaneBrush(QColor(0, 255, 0));
  painter.setBrush(PlaneBrush);
  painter.setPen(Qt::NoPen);

  // display the guidance line
  std::list<shapeData*>::iterator it;
  for(it  = GeoShapeData::listShapeData.begin();
      it != GeoShapeData::listShapeData.end(); ++it)
  {
      shapeData* pData = *it;
      if(0 != pData->pVoid && pData->type == shapeData::point)
      {
          QPointF* pPoint = (QPointF*)(pData->pVoid);
          QPointF _p = *pPoint;
          //_p -= GeoShapeData::geoRect.center();
          //_p -= geoRect.topLeft();
          _p -= geoRect.center();
          _p *= scale;
          painter.drawEllipse(_p, 4, 4);
      }
  }
}

void drawAirPlaneTrail::draw(QPainter &painter)
{
  // display airplane trail
  QPen pen;
  QPolygonF qPolygon(GeoShapeData::vtrAirplaneTrail);
  mypolygon mPolygon;
  mPolygon.setCore(qPolygon);
  mPolygon.optimizeCoord(geoRect.center(), scale);
  QVector<qreal> dashes;
  dashes << 2 << 2 << 2 << 2;
  pen.setDashPattern(dashes);
  pen.setColor(QColor(199, 237, 204));
  pen.setWidth(2);
  painter.setPen(pen);
  painter.drawPolyline(mPolygon.getCore());
}

void drawGeographicalPolyline::draw(QPainter &painter)
{
    QPen pen(QColor(35, 7, 188));
    pen.setWidth(1);
    painter.setPen(pen);

    // display the guidance line
    std::list<shapeData*>::iterator it;
    for(it  = GeoShapeData::listShapeData.begin();
        it != GeoShapeData::listShapeData.end(); ++it)
    {
        shapeData* pData = *it;
        if(0 != pData->pVoid && pData->type == shapeData::polyline)
        {
            QPolygonF* pPolygon = (QPolygonF*)(pData->pVoid);
            mypolygon polygon;
            polygon.setCore(*pPolygon);
            //polygon.optimizeCoord(geoRect.topLeft(), scale);
            polygon.optimizeCoord(geoRect.center(), scale);
            painter.drawPolyline(polygon.getCore());
        }
    }
}

void drawGeographicalPolygon::draw(QPainter &painter)
{
  QBrush PlaneBrush(QColor(0, 100, 0));
  painter.setBrush(PlaneBrush);
  painter.setPen(Qt::NoPen);

  std::list<shapeData*>::iterator it;
  for (it = GeoShapeData::listShapeData.begin();
       it != GeoShapeData::listShapeData.end(); ++it)
  {
      shapeData* pData = *it;
      if(0 != pData->pVoid && pData->type == shapeData::area)
      {
          QPolygonF* pPolygon = (QPolygonF*)(pData->pVoid);
          mypolygon polygon;
          polygon.setCore(*pPolygon);
          //polygon.optimizeCoord(geoRect.topLeft(), scale);
          polygon.optimizeCoord(geoRect.center(), scale);
          painter.drawPolygon(polygon.getCore());
      }
  }
}

//void drawAirPlane::draw(QPainter &painter)
//{
//  if (airPlane != QPointF(.0, .0))
//    {
//      QBrush PlaneBrush(QColor(240, 0, 0));
//      painter.setBrush(PlaneBrush);
//      painter.setPen(Qt::NoPen);
//      airPlane -= geoRect.topLeft();
//      airPlane *= scale;
//      painter.drawEllipse(airPlane, 4, 4);
//    }
//}
