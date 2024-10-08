#pragma once

#include "uiPrerequisites.h"
#include "uiClassRegisters.h"

#include "uiPawn.h"

class Animator;
class AudioSource;
class BoxCollider;

class CreatureEntity : public PawnEntity
{
public:

  CreatureEntity() = default;

  CreatureEntity(const String& newName, 
           const float& newMaxHP = 1, 
           const float& newDamage = 1, 
           const float& newDroppableXP = 1) : PawnEntity(newName)
  {
    m_attack = newDamage;
    m_maxHp = newMaxHP;
    m_hp = m_maxHp;
    m_droppableXP = newDroppableXP;
  }

  ~CreatureEntity() = default;

  virtual void GetDamage(const float& damage);

  float m_attack;
  float m_hp;
  float m_maxHp;

  float m_droppableXP;

  Callback<void> m_onHPZero;

};

REGISTER_CLASS(CreatureEntity)

