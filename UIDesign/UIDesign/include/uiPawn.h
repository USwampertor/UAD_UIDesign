#pragma once

#include "uiPrerequisites.h"
#include "uiClassRegisters.h"
#include "uiEntity.h"

class PawnEntity : public Entity
{
public:
  PawnEntity() = default;

  PawnEntity(const String& newName) : Entity(newName) {}

  ~PawnEntity() = default;

  void AutoPossess();
};

REGISTER_CLASS(PawnEntity)