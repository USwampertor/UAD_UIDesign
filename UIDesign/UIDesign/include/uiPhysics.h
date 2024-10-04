#pragma once

#include "uiPrerequisites.h"

#include "uiModule.h"
#include "uiCollision.h"
#include "uiVector2.h"

BETTER_ENUM(ePHYSICLAYERS, 
            uint32, 
            DEFAULT       = 0,
            PROJECTILES   = 1
            // ADD MORE AS NEEDED
            )


class BoxCollider;

class Physics : public Module<Physics>
{
public:
  virtual void OnStartUp() override
  {
    m_world = MakeUniqueObject<World>(Vector2f(0, 0));
  }

  void SetGravity(const Vector2f& gravity);

  void RegisterPhysicsBody(PhysicsBody& toRegister);

  void UnRegisterPhysicsBody(PhysicsBody& toRegister);

  void Update(const float& delta);

  UniquePtr<World> m_world;

  // Vector<BoxCollider*> m_physicObjects;
};

