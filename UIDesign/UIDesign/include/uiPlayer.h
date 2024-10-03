#pragma once

#include "uiPrerequisites.h"

#include "uiBoxCollider.h"
#include "uiCreature.h"
#include "uiInput.h"
#include "uiInputAction.h"
#include "uiInputMapping.h"
#include "uiUtilities.h"

class Animator;
class AudioSource;
class AudioListener;

class PlayerEntity : public Creature
{
public:
  PlayerEntity() = default;

  PlayerEntity(const String& name) : Creature(name) {}

  ~PlayerEntity() = default;

  void PlayerDeath();

  virtual void Initialize();

  void Update(const float& delta) override;

  void Up(SharedPtr<InputValue> value);

  void Down(SharedPtr<InputValue> value);

  void Left(SharedPtr<InputValue> value);

  void Right(SharedPtr<InputValue> value);

  void PlaySound(SharedPtr<InputValue> value);

  void EnterCollision(const PhysicsCollisionResult& c);

  void StayCollision(const PhysicsCollisionResult& c);

  void ExitCollision(const PhysicsCollisionResult& c);

  void OnPlayerDeath();

  virtual void GetDamage(const float& damage);

  float m_speed = 15;

  float m_damageTimer = 0;

  // float m_life = 10;

  Vector2f m_direction;

  BoxCollider* m_collider = nullptr;

  Animator* m_animator = nullptr;

  AudioSource* m_source = nullptr;

  AudioListener* m_listener = nullptr;

  SharedPtr<InputMapping> m_map;

  Entity* m_sword;

};

