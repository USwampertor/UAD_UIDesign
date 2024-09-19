#pragma once

#include "uiPrerequisites.h"

#include "uiPawn.h"
class Player : public Pawn
{
  Player() = default;

  ~Player() = default;

  void PlayerDeath();
};

