#include "uiparamconfig.h"

ViewDirection UIParamConfig::dir = PolarHeading;
int UIParamConfig::shootModel = 0;
int UIParamConfig::returnBase = 0;
int UIParamConfig::distanceTolerance = 0;
int UIParamConfig::heightTolerance = 0;
int UIParamConfig::designedHeight = 0;

UIParamConfig::UIParamConfig()
{
}

void UIParamConfig::setViewDirection(ViewDirection _dir)
{
  dir = _dir;
}

ViewDirection UIParamConfig::getViewDirection()
{
  return dir;
}

void UIParamConfig::setShootModel(int vle)
{
  shootModel = vle;
}

int UIParamConfig::getShootModel()
{
  return shootModel;
}

void UIParamConfig::setReturnBase(int vle)
{
  returnBase = vle;
}

int UIParamConfig::getReturnBase()
{
    return returnBase;
}

void UIParamConfig::setDistanceTolerance(int vle)
{
    distanceTolerance = vle;
}

int UIParamConfig::getDistanceTolerance()
{
    return distanceTolerance;
}

void UIParamConfig::setHeightTolerance(int vle)
{
    heightTolerance = vle;
}

int UIParamConfig::getHeightTolerance()
{
    return heightTolerance;
}

void UIParamConfig::setDesignedHeight(int vle)
{
    designedHeight = vle;
}

int UIParamConfig::getDesignedHeight()
{
    return designedHeight;
}

bool UIParamConfig::validTolerance()
{
    if (0 == heightTolerance ||
        0 == distanceTolerance)
    {
        return false;
    }
    else
        return true;
}
