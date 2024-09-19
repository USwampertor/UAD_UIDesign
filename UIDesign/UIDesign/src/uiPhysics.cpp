#include "uiPhysics.h"

#include "uiBoxCollider.h"

void Physics::SetGravity(const Vector2f& gravity)
{
  // m_world->gravity = gravity;
}

void Physics::RegisterPhysicsBody(PhysicsBody& toRegister)
{
  m_world->AddPhysicsBody(toRegister);
  // m_physicObjects.push_back(reinterpret_cast<BoxCollider*>(&toRegister));
}

void Physics::UnRegisterPhysicsBody(PhysicsBody& toRegister)
{
  // for (BoxCollider* obj : m_physicObjects)
  // {
  //   if (obj != reinterpret_cast<BoxCollider*>(&toRegister))
  //   {
  //     obj->UnregisterCollisionResult(toRegister);
  //   }
  // }
  BoxCollider* toDelete = static_cast<BoxCollider*>(&toRegister);
  // toDelete->UnregisterCollisionResult();

  for (PhysicsCollisionResult* c : toDelete->m_collisions)
  {
    int i = 0;
    BoxCollider* toRemove = static_cast<BoxCollider*>(&c->object2);
    for (PhysicsCollisionResult* c1 : toRemove->m_collisions)
    {
      if (c1->object2 == *toDelete)
      {
        toRemove->m_collisions.erase(toRemove->m_collisions.begin() + i);
      }
      ++i;
    }
  }

  m_world->RemovePhysicsBody(toRegister);
//   for (auto el : m_world->removalList)
//   {
//     m_world->objects.remove(el);
//   }
}

void Physics::Update(const float& delta)
{
  m_world->UpdatePhysics(delta);
}