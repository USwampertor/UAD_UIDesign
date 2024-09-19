#pragma once
#include "uiCreature.h"

class Enemy : public Creature
{
  Enemy() = default;

  ~Enemy() = default;

  Enemy(const float& newMaxLife, const float& newDamage)
  {
    m_maxHp = newMaxLife;
    m_hp = m_maxHp;

    m_attack = newDamage;

    m_onHPZero = std::bind(&Enemy::OnEnemyDeath, this);
  }

  void OnEnemyDeath();


};

