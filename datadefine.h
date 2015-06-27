#ifndef DATADEFINE_H
#define DATADEFINE_H


#include <QPointF>
#include <string>

typedef struct shapeData
{
  /*
   * point represents by (x, y, z)
   * line represents by two points
   * area represents by serious points
   * guidance represents by serious points who have direction
   */
  enum ShapeType{point, line, area, guidance, polyline, airplane, airplanetrail, guidanceline};

  shapeData(void* _data, ShapeType t, int nNums = 1)
  { pVoid = _data; type = t; nNumofShape = nNums; }

  ShapeType type;
  void*     pVoid;
  int       nNumofShape;
} *shapeDataPtr;

typedef struct GuidancePoint
{
    enum GPType
    {
        AirPort,
        A1Type,
        A2Type,
        B1Type,
        B2Type,
        Normal
    };
    GuidancePoint(GPType t, QPointF p, int lVle=0, int pVle=0)
    { type = t; point = p; nLineNum = lVle; nPointNum = pVle; }

    int     nLineNum;  // belong to which line
    int     nPointNum; // the sequence number
    GPType  type;
    QPointF point;

} *GuidancePointPtr;

typedef struct AirPlane
{
  QPointF pos;
  QPointF nextPos;
  double  hgt;
  double  Fhgt;
  int status;
  std::string cLineIdx;
  std::string cPointIdx;
  std::string FlineIdx;
  std::string FpointIdx;
  double speed;
  double angle;
  double aoy;
  double distance;
  double az;
  double designAngle;
} *AirPlanePtr;

#endif // DATADEFINE_H
