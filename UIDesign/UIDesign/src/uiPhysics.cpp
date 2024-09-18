#include "uiPhysics.h"


void Physics::SetGravity(const Vector2f& gravity)
{
  m_world = { gravity };
}

void Physics::RegisterPhysicsBody(PhysicsBody& toRegister)
{
  m_world.AddPhysicsBody(toRegister);
}

void Physics::UnRegisterPhysicsBody(PhysicsBody& toRegister)
{
  m_world.RemovePhysicsBody(toRegister);
}

void Physics::Update(const float& delta)
{
  m_world.UpdatePhysics(delta);
}