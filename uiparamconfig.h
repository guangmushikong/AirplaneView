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

  static void setShootModel(int);
  static int  getShootModel();

  static void setReturnBase(int);
  static int  getReturnBase();

  static void setDistanceTolerance(int);
  static int  getDistanceTolerance();

  static void setHeightTolerance(int);
  static int  getHeightTolerance();

  static void setDesignedHeight(int);
  static int  getDesignedHeight();

  static bool validTolerance();

protected:
  static ViewDirection dir;
  static int shootModel; // 0-Normal; 1-ReShoot
  static int returnBase; // 0-No; 1-Yes
  static int distanceTolerance;
  static int heightTolerance;

  static int designedHeight;
};

#endif // UIPARAMCONFIG_H
