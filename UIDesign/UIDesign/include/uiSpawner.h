#pragma once
#include "uiPrerequisites.h"
#include "uiClassRegisters.h"

#include "uiEntity.h"
class SpawnerEntity : public Entity
{
public:
  SpawnerEntity() = default;

  SpawnerEntity(const String& newName) : Entity(newName) {}

  ~SpawnerEntity() = default;

  void SpawnEnemy()
  {

  }


  float m_lifetime = 0;
};

REGISTER_CLASS(SpawnerEntity)
