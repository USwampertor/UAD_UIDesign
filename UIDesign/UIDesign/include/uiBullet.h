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

  void Up()
  {
    this->Move(Vector2f(0, -1));
  }

  void Down()
  {
    this->Move(Vector2f(0, 1));
  }

  void Left()
  {
    this->Move(Vector2f(-1, 0));
  }

  void Right()
  {
    this->Move(Vector2f(0, 1));
  }

};

