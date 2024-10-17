#pragma once
#include "uiPrerequisites.h"
#include "uiClassRegisters.h"

#include "uiEntity.h"
class SpawnerEntity : public Entity
{
public:

  static String GetType() { return "SpawnerEntity"; }

  SpawnerEntity() = default;

  SpawnerEntity(const String& newName) : Entity(newName) {}

  ~SpawnerEntity() = default;

  virtual JSONDocument Serialize() override;

  void SpawnEnemy()
  {

  }


  float m_lifetime = 0;
};

REGISTER_CLASS(SpawnerEntity)
