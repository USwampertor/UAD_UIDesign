#pragma once

#include "uiPrerequisites.h"

#include "uiEntity.h"

class Pawn;

class Controller : public Entity
{
  void PossesPawn(SharedPtr<Pawn> newPawm);

  void UnPossesPawn();

  SharedPtr<Pawn> m_pawn;
};

