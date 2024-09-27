#include "uiBoxCollider.h"

#include "uiPhysics.h"

#include "uiEntity.h"

void BoxCollider::collisionCallback(PhysicsCollisionResult& collision)
{
  bool existing = false;
  // for (const SharedPtr<PhysicsCollisionResult>& obj : m_collisions)
  for (const PhysicsCollisionResult* obj : m_collisions)
  {
    // if (obj->object2 == collision.object2)
    if (obj->object2 == collision.object2)
    {
      existing = true;
      break;
    }
  }
  if (existing)
  {
    OnCollisionStay(collision);
  }
  else
  {
    // m_collisions.push_back(MakeSharedObject<PhysicsCollisionResult>(collision));
    if (static_cast<BoxCollider*>(&collision.object2)->m_parent->GetName() == "Player" && m_parent->GetName() == "bullet")
    {
      int dummy = 0;
    }
    m_collisions.push_back(new PhysicsCollisionResult(collision));
    OnCollisionEnter(collision);
  }
}

void BoxCollider::updateCallback(unsigned int deltaMs)
{
  if (!this->getStatic())
  {
    m_parent->SetPosition(this->getCenter());
  }
  int i = 0;
  for (Vector<PhysicsCollisionResult*>::iterator it = m_collisions.begin();
       it != m_collisions.end(); 
       ++it)
  {
    PhysicsCollisionResult* i = *it;
    if (!i->object1.collideWith(i->object2).hasCollided)
    {
      if (static_cast<BoxCollider*>(&i->object2)->m_parent->GetName() == "Player" && m_parent->GetName() == "bullet")
      {
        int dummy = 0;
      }
      if (!m_parent->m_markedToDestroy)
      {
        OnCollisionExit(*i);
        it = m_collisions.erase(it);
        if (it == m_collisions.end())
        {
          break;
        }
      }
    }
  }
}

void BoxCollider::PropagateTransform(const Transform2D& newTransform)
{
  Vector2f newPosition = newTransform.position + m_offset->position;
  setCenter(newPosition);
}

void BoxCollider::Update(const float& delta)
{
  
}

void BoxCollider::Initialize()
{
  m_collisions.clear();
  m_onCollisionEnterCallbackList.clear();
  m_onCollisionStayCallbackList.clear();
  m_onCollisionExitCallbackList.clear();
  m_offset->Reset();
  setFillColor(sf::Color::Transparent);
  setOutlineColor(sf::Color::Red);
  setOutlineThickness(2);
  Physics::Instance().RegisterPhysicsBody(*this);
}

void BoxCollider::OnDestroy()
{
  // for (auto& c : m_collisions)
  // {
  //   c
  // }
  // for (int j = 0; j < m_collisions.size(); ++j)
  // {
  //   BoxCollider* other = static_cast<BoxCollider*>(&m_collisions[j]->object2);
  //   for (Vector<PhysicsCollisionResult*>::iterator it = other->m_collisions.begin();
  //     it != other->m_collisions.end();
  //     ++it)
  //   {
  //     PhysicsCollisionResult* i = *it;
  //     if (i->object2 == *(static_cast<PhysicsBody*>(this)) )
  //     {
  //       it = m_collisions.erase(it);
  //       if (it == m_collisions.end())
  //       {
  //         break;
  //       }
  //     }
  //   }
  // }
  Physics::Instance().UnRegisterPhysicsBody(*this);
  m_collisions.clear();
}

void BoxCollider::AddCollisionEnterCallback(const CollisionCallback& c)
{
  m_onCollisionEnterCallbackList.push_back(c);
}

void BoxCollider::AddCollisionStayCallback(const CollisionCallback& c)
{
  m_onCollisionStayCallbackList.push_back(c);
}

void BoxCollider::AddCollisionExitCallback(const CollisionCallback& c)
{
  m_onCollisionExitCallbackList.push_back(c);
}

void BoxCollider::OnCollisionEnter(const PhysicsCollisionResult& collision)
{
  for (int i = 0; i < m_onCollisionEnterCallbackList.size(); ++i)
  {
    m_onCollisionEnterCallbackList[i](collision);
  }
}

void BoxCollider::OnCollisionStay(const PhysicsCollisionResult& collision)
{
  for (int i = 0; i < m_onCollisionStayCallbackList.size(); ++i)
  {
    m_onCollisionStayCallbackList[i](collision);
  }
}

void BoxCollider::OnCollisionExit(const PhysicsCollisionResult& collision)
{
  for (int i = 0; i < m_onCollisionExitCallbackList.size(); ++i)
  {
    m_onCollisionExitCallbackList[i](collision);
  }
}




