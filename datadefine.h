#ifndef DATADEFINE_H
#define DATADEFINE_H


#include <QPointF>

typedef struct shapeData
{
  /*
   * point represents by (x, y, z)
   * line represents by two points
   * area represents by serious points
   * guidance represents by serious points who have direction
   */
  enum ShapeType{point, line, area, guidance, polyline, airplane, airplanetrail};

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
  double  hgt;
  int status;
  int lineIdx;
  int pointIdx;
  double speed;
  double angle;
} *AirPlanePtr;

#endif // DATADEFINE_H
