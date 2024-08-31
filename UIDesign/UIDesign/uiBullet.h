#pragma once

#include "uiUtilities.h"
#include "uiEntity.h"
#include "uiAnimator.h"
#include "uiBoxCollider.h"

class Bullet : Entity
{

  BoxCollider* collider;
  Animator* animator;

  virtual void Initialize() override 
  {
    CreateComponent<BoxCollider>();
    CreateComponent<Animator>();
  
  }
};

