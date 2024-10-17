#pragma once

#include "uiPrerequisites.h"
#include "uiClassRegisters.h"
#include "uiEntity.h"

class PawnEntity : public Entity
{
public:
  static String GetType() { return "PawnEntity"; }

  PawnEntity() = default;

  PawnEntity(const String& newName) : Entity(newName) {}

  ~PawnEntity() = default;

  virtual JSONDocument Serialize() override;

  void AutoPossess();
};

REGISTER_CLASS(PawnEntity)
