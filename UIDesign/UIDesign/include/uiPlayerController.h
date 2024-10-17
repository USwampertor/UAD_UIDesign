#pragma once
#include "uiPrerequisites.h"
#include "uiClassRegisters.h"

#include "uiController.h"
class PlayerControllerEntity : public ControllerEntity
{
  static String GetType() { return "PlayerControllerEntity"; }

};

REGISTER_CLASS(PlayerControllerEntity)
