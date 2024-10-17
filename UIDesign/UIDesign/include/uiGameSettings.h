#pragma once

#include "uiPrerequisites.h"
#include "uiClassRegisters.h"
#include "uiEntity.h"

class GameSettings : Entity
{
  static String GetType() { return "GameSettings"; }

  virtual void OnGameStart() {}
  
  virtual void OnGameRestart() {}
  
  String m_controllerType = "none";

  String m_playerType = "none";
  
};

REGISTER_CLASS(GameSettings)
