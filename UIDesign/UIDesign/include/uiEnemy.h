#pragma once
#include "uiCreature.h"
#include "uiUtilities.h"

class EnemyEntity : public Creature
{
public:

  EnemyEntity() = default;

  // EnemyEntity(const String& newName) : Creature(newName) {}

  ~EnemyEntity() = default;

  EnemyEntity(const String& newName) : Creature(newName)
  {
    // m_maxHp = newMaxLife;
    m_hp = m_maxHp;

    // m_attack = newDamage;

    m_onHPZero = std::bind(&EnemyEntity::OnEnemyDeath, this);
    m_timeBeforeSpawn = std::rand() % 10 + 5;
  }


  virtual void Update(const float& delta) override;

  void OnEnemyDeath();

  float m_timeBeforeSpawn;
};

