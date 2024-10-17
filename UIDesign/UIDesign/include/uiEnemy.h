#pragma once

#include "uiPrerequisites.h"
#include "uiClassRegisters.h"

#include "uiCreature.h"


class Animator;
class AudioSource;
class BoxCollider;

class EnemyEntity : public CreatureEntity
{
public:

  static String GetType() { return "EnemyEntity"; }

  EnemyEntity() = default;

  ~EnemyEntity() = default;

  EnemyEntity(const String& newName) : CreatureEntity(newName) {}

  virtual void Initialize() override;

  virtual void Update(const float& delta) override;

  virtual JSONDocument Serialize() override;

  void OnEnemyDeath();

  float m_timeBeforeSpawn = 0;

  Animator* m_animator = nullptr;
  AudioSource* m_source = nullptr;
  BoxCollider* m_collider = nullptr;
};

REGISTER_CLASS(EnemyEntity)
