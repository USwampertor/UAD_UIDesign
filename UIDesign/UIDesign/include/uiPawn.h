#pragma once

#include "uiPrerequisites.h"

#include "uiEntity.h"
class Pawn : public Entity
{
public:
  Pawn() = default;
  ~Pawn() = default;

  void AutoPossess();
};
