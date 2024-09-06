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

  void Up(InputCallback value)
  {
    this->Move(Vector2f(0, -1));
  }

  void Down(InputCallback value)
  {
    this->Move(Vector2f(0, 1));
  }

  void Left(InputCallback value)
  {
    this->Move(Vector2f(-1, 0));
  }

  void Right(InputCallback value)
  {
    this->Move(Vector2f(0, 1));
  }

};

