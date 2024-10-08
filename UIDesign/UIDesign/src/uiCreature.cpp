#include "uiCreature.h"


void CreatureEntity::GetDamage(const float& damage)
{
  m_hp -= damage;
  if (m_hp <= 0)
  {
    m_onHPZero();
  }
}

