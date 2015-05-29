#ifndef COORDTRANSLATE_H
#define COORDTRANSLATE_H

#include <QRectF>

template<class T>
class CoordTranslate
{
public:
  CoordTranslate(){}
  ~CoordTranslate(){}

public:
  void Pixel2World(QRectF r, double scale, T& data)
  {
    data /= scale;
    data += r.center();
  }
  void World2Pixel(QRectF r, double scale, T& data)
  {
    data -= r.center();
    data *= scale;
  }
};

#endif // COORDTRANSLATE_H
