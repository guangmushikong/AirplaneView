#ifndef MAPTOOL_H
#define MAPTOOL_H

#include <QPointF>

class PaintArea;

class MapTool
{
public:
  MapTool(PaintArea* view);
  virtual ~MapTool();

public:
  virtual void OnLButtonUp(QPointF p){}
  virtual void OnLButtonDown(QPointF p){}
  virtual void OnWheelZoom(double _scale, QPoint mouse){}

protected:
  PaintArea* pView;
};

class MapToolPan : public MapTool
{
public:
  MapToolPan(PaintArea* view);
  ~MapToolPan();

public:
  virtual void OnLButtonUp(QPointF p);
  virtual void OnLButtonDown(QPointF p);

private:
  bool bMapMoving;
};

class MapToolZoom : public MapTool
{
public:
  MapToolZoom(PaintArea* view);
  ~MapToolZoom();

public:
  virtual void OnWheelZoom(double _scale, QPoint mouse);
};

#endif // MAPTOOL_H
