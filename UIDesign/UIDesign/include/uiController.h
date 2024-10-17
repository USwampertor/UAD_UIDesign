#pragma once

#include "uiPrerequisites.h"
#include "uiClassRegisters.h"

#include "uiEntity.h"

class PawnEntity;

class ControllerEntity : public Entity
{
public:

  static String GetType() { return "ControllerEntity"; }

  void PossesPawn(SharedPtr<PawnEntity> newPawm);

  void UnPossesPawn();

  void AutoPossess();

  SharedPtr<PawnEntity> m_pawn;
};

REGISTER_CLASS(ControllerEntity)
