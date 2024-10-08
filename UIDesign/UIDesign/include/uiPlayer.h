#pragma once

#include "uiPrerequisites.h"
#include "uiClassRegisters.h"

#include "uiCreature.h"
#include "uiJSON.h"
#include "uiInputMapping.h"
#include "uiCollision.h"
#include "uiUtilities.h"
#include "uiVector2.h"

class Animator;
class InputValue;
class AudioSource;
class AudioListener;
class BoxCollider;

class PlayerEntity : public CreatureEntity
{
public:

  static String GetType() { return "PlayerEntity"; }

  PlayerEntity() = default;

  ~PlayerEntity() = default;

  PlayerEntity(const String& name) : CreatureEntity(name) {}


  virtual void Initialize() override;

  virtual void Update(const float& delta) override;

  virtual JSONDocument Serialize() override;

  void PlayerDeath();

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

  Entity* m_sword = nullptr;

};

REGISTER_CLASS(PlayerEntity)
