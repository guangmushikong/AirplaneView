#ifndef UIPARAMCONFIG_H
#define UIPARAMCONFIG_H

enum ViewDirection
{
  PolarHeading = 0,
  PlaneHeading
};

class UIParamConfig
{
public:
  UIParamConfig();

  static void setViewDirection(ViewDirection);
  static ViewDirection getViewDirection();

protected:
  static ViewDirection dir;
};

#endif // UIPARAMCONFIG_H
