#include "maptool.h"
#include "paintarea.h"

MapTool::MapTool(PaintArea* view):pView(view)
{
}

MapTool::~MapTool()
{}

MapToolPan::MapToolPan(PaintArea *view):MapTool(view)
{}

MapToolPan::~MapToolPan()
{}

void MapToolPan::OnLButtonDown(QPointF p)
{
  pView->panStart(p);
}

void MapToolPan::OnLButtonUp(QPointF p)
{
  pView->panEnd(p);
}


MapToolZoom::MapToolZoom(PaintArea *view):MapTool(view)
{}

MapToolZoom::~MapToolZoom()
{}

void MapToolZoom::OnWheelZoom(double _scale)
{
  if (_scale > .0)
    pView->Zoom(_scale);
}
