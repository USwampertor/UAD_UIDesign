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
    CreateComponent<BoxCollider>();
    CreateComponent<Animator>();
  }

  SharedPtr<InputMapping> m_map;

  void Update(const float& delta) override
  {
    Entity::Update(m_speed);

    Move(m_direction * delta * m_speed * 0.01f);
  }

  void Up(SharedPtr<InputValue> value)
  {
    // this->Move(Vector2f(0, -1));
    if (value->GetState() == Input::eINPUTSTATE::PRESSED ||
        value->GetState() == Input::eINPUTSTATE::HELD)
    {
      m_direction.y = -1;
    }
    else
    {
      m_direction.y = 0;
    }
  }

  void Down(SharedPtr<InputValue> value)
  {
    if (value->GetState() == Input::eINPUTSTATE::PRESSED ||
        value->GetState() == Input::eINPUTSTATE::HELD)
    {
      m_direction.y = -1;
    }
    else
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
    else
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
    else
    {
      m_direction.x = 0;
    }
  }

  float m_speed = 10;

  Vector2f m_direction;

};

