#pragma once
#include "uiCreature.h"
#include "uiUtilities.h"

class Animator;
class AudioSource;
class BoxCollider;

class EnemyEntity : public Creature
{
public:

  EnemyEntity() = default;

  // EnemyEntity(const String& newName) : Creature(newName) {}

  ~EnemyEntity() = default;

  EnemyEntity(const String& newName) : Creature(newName) {}

  virtual void Initialize();

  virtual void Update(const float& delta) override;

  void OnEnemyDeath();

  float m_timeBeforeSpawn;

  Animator* m_animator = nullptr;
  AudioSource* m_source = nullptr;
  BoxCollider* m_collider = nullptr;
};

