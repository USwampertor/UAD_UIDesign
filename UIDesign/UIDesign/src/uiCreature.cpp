#include "uiCreature.h"


void Creature::GetDamage(const float& damage)
{
  // m_hp -= damage;
  if (m_hp <= 0)
  {
    m_onHPZero();
  }
}

