#pragma once

#include "uiPrerequisites.h"

#include "uiUtilities.h"

#include "uiPawn.h"


class Animator;

class BoxCollider;

class AudioSource;

class Creature : public Pawn
{
public:

  Creature() = default;

  Creature(const String& newName, const float& newMaxHP = 1, const float& newDamage = 1, const float& newDroppableXP = 1) : Pawn(newName)
  {
    m_attack = newDamage;
    m_maxHp = newMaxHP;
    m_hp = m_maxHp;
    m_droppableXP = newDroppableXP;
  }

  ~Creature() = default;

  void GetDamage(const float& damage);

  float m_attack;
  float m_hp;
  float m_maxHp;

  float m_droppableXP;

  Callback<void> m_onHPZero;

};

