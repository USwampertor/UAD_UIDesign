#pragma once

#include "uiPrerequisites.h"

#include "uiAnimator.h"
#include "uiAudioSource.h"
#include "uiBoxCollider.h"
#include "uiEntity.h"
#include "uiResourceManager.h"
#include "uiUtilities.h"

class BulletEntity : public Entity
{
public:

  BulletEntity() = default;

  ~BulletEntity() = default;

  BulletEntity(const String& newName) : Entity(newName) {}

  virtual void Initialize();

  void Update(const float& delta) override
  {
    Entity::Update(delta);
  }


  void EnterCollision(const PhysicsCollisionResult& c);


  Vector2f m_direction;

  BoxCollider* m_collider = nullptr;

  Animator* m_animator = nullptr;

  AudioSource* m_source = nullptr;

  // String isColliding = "";

};

