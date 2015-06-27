#include "uiparamconfig.h"

ViewDirection UIParamConfig::dir = PolarHeading;

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
