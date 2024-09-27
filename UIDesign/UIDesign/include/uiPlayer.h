#pragma once

#include "uiPrerequisites.h"

#include "uiAnimator.h"
#include "uiAudioSource.h"
#include "uiBoxCollider.h"
#include "uiCreature.h"
#include "uiInput.h"
#include "uiInputAction.h"
#include "uiInputMapping.h"
#include "uiUtilities.h"

class PlayerEntity : public Creature
{
public:
  PlayerEntity() = default;

  PlayerEntity(const String& name) : Creature(name)
  {

  }

  ~PlayerEntity() = default;

  void PlayerDeath();

  virtual void Initialize()
  {
    Entity::Initialize();
    m_collider = CreateComponent<BoxCollider>();
    m_animator = CreateComponent<Animator>();
    m_source = CreateComponent<AudioSource>();
    m_collider->setSize(Vector2f(1, 1));
    m_collider->setLayer(1, 1);
    m_collider->setLayer(0, 1);
    m_collider->m_parent = this;
    m_maxHp = 10;
    m_hp = m_maxHp;
    // m_collider->AddCollisionEnterCallback(std::bind(&BulletEntity::EnterCollision, this, std::placeholders::_1));
    // m_collider->AddCollisionStayCallback(std::bind(&BulletEntity::StayCollision, this, std::placeholders::_1));
    // m_collider->AddCollisionExitCallback(std::bind(&BulletEntity::ExitCollision, this, std::placeholders::_1));
  }


  void PrintCollision(sfp::PhysicsBodyCollisionResult&)
  {
    // isColliding = "COLLISION";
  }

  void Update(const float& delta) override
  {
    Entity::Update(delta);
    Move(m_direction * delta * m_speed * 0.01f);
    if ((m_direction.x != 0 || m_direction.y != 0) && m_animator->m_animationName.compare("walking") != 0)
    {
      m_animator->Stop();
      m_animator->SetAnimation("walking");
      m_animator->Play();
    }
    else if (m_direction.x == 0 && m_direction.y == 0 && m_animator->m_animationName.compare("idle") != 0)
    {
      m_animator->Stop();
      m_animator->SetAnimation("idle");
      m_animator->Play();
    }
  }

  void Up(SharedPtr<InputValue> value)
  {
    if (value->GetState() == Input::eINPUTSTATE::PRESSED ||
      value->GetState() == Input::eINPUTSTATE::HELD)
    {
      m_direction.y = -1;
    }
    else if (value->GetState() == Input::eINPUTSTATE::RELEASED)
    {
      m_direction.y = 0;
    }
  }

  void Down(SharedPtr<InputValue> value)
  {
    if (value->GetState() == Input::eINPUTSTATE::PRESSED ||
      value->GetState() == Input::eINPUTSTATE::HELD)
    {
      m_direction.y = 1;
    }
    else if (value->GetState() == Input::eINPUTSTATE::RELEASED)
      // else
    {
      m_direction.y = 0;
    }
  }

  void Left(SharedPtr<InputValue> value)
  {
    if (value->GetState() == Input::eINPUTSTATE::PRESSED ||
      value->GetState() == Input::eINPUTSTATE::HELD)
    {
      m_direction.x = -1;
      if (m_animator->GetSprite().m_flippedX)
      {
        m_animator->GetSprite().Flip();
      }
    }
    else if (value->GetState() == Input::eINPUTSTATE::RELEASED)
      // else
    {
      m_direction.x = 0;
    }
  }

  void Right(SharedPtr<InputValue> value)
  {
    if (value->GetState() == Input::eINPUTSTATE::PRESSED ||
      value->GetState() == Input::eINPUTSTATE::HELD)
    {
      m_direction.x = 1;
      
      if (!m_animator->GetSprite().m_flippedX)
      {
        m_animator->GetSprite().Flip();
      }
    }
    else if (value->GetState() == Input::eINPUTSTATE::RELEASED)
    {
      m_direction.x = 0;
    }
  }

  void PlaySound(SharedPtr<InputValue> value)
  {
    if (value->GetState() == Input::eINPUTSTATE::PRESSED)
    {
      m_source->PlayOnce();
      std::cout << "Play" << std::endl;
    }
  }

  void EnterCollision(const PhysicsCollisionResult& c);

  void StayCollision(const PhysicsCollisionResult& c)
  {
  }
  void ExitCollision(const PhysicsCollisionResult& c)
  {
  }

  float m_speed = 15;

  // float m_life = 10;

  Vector2f m_direction;

  BoxCollider* m_collider = nullptr;

  Animator* m_animator = nullptr;

  AudioSource* m_source = nullptr;

  String isColliding = "";

  SharedPtr<InputMapping> m_map;

};

