#pragma once

#include "uiPrerequisites.h"

#include "uiModule.h"

#include <SFPhysics/SFPhysics.h>

using PhysicsBody = sfp::PhysicsBody;

class Physics : public Module<Physics>
{
public:
  virtual void OnStartUp() override
  {
    m_world = { Vector2f(0,0) };
  }

  void SetGravity(const Vector2f& gravity);

  void RegisterPhysicsBody(PhysicsBody& toRegister);

  void UnRegisterPhysicsBody(PhysicsBody& toRegister);

  void Update(const float& delta);

  sfp::World m_world;
};

