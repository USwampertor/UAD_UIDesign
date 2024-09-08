#pragma once

#include "uiAnimator.h"
#include "uiBoxCollider.h"
#include "uiEntity.h"
#include "uiInput.h"
#include "uiInputAction.h"
#include "uiInputMapping.h"
#include "uiUtilities.h"

class BulletEntity : public Entity
{
public:

  virtual void Initialize()
  {
    Entity::Initialize();
    m_collider = CreateComponent<BoxCollider>();
    m_animator = CreateComponent<Animator>();
    m_collider->setSize(Vector2f(1,1));
  }

  SharedPtr<InputMapping> m_map;

  void PrintCollision(sfp::PhysicsBodyCollisionResult&)
  {
    isColliding = "COLLISION";
  }

  void Update(const float& delta) override
  {
    Entity::Update(m_speed);
    Move(m_direction * delta * m_speed * 0.01f);
    if (m_animator->GetState() == eANIMATIONSTATE::STOPPED &&
        (m_direction.x != 0 || m_direction.y != 0))
    {
      m_animator->Play();
    }
    else if (m_direction.x == 0 && m_direction.y == 0)
    {
      m_animator->Stop();
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
    }
    else if (value->GetState() == Input::eINPUTSTATE::RELEASED)
    {
      m_direction.x = 0;
    }
  }

  float m_speed = 10;

  Vector2f m_direction;

  SharedPtr<BoxCollider> m_collider;

  SharedPtr<Animator> m_animator;

  String isColliding = "";
};

