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
    BoxCollider* other = static_cast<BoxCollider*>(&c->object2);
    for (Vector<PhysicsCollisionResult*>::iterator it = other->m_collisions.begin();
      it != other->m_collisions.end();
      ++it)
    {
      PhysicsCollisionResult* i = *it;
      if (i->object2 == toRegister)
      {
        toDelete->OnCollisionExit(*c);

        it = other->m_collisions.erase(it);
        if (it == other->m_collisions.end())
        {
          break;
        }
      }
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