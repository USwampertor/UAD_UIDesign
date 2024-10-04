#pragma once

#include "uiPrerequisites.h"

#include "uiEntity.h"

class Pawn : public Entity
{
public:
  Pawn() = default;

  Pawn(const String& newName) : Entity(newName) {}

  ~Pawn() = default;

  void AutoPossess();
};
