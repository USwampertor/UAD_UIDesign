#pragma once

#include "uiPrerequisites.h"

#include "uiUtilities.h"
#include "uiComponent.h"

#include <SFPhysics/SFPhysics.h>

#include <iostream>

using PhysicsCollisionResult =  sfp::PhysicsBodyCollisionResult;
using CollisionCallback = Callback<void, const PhysicsCollisionResult&>;
using PhysicsRectangle = sfp::PhysicsRectangle;
using PhysicsBody = sfp::PhysicsBody;



class BoxCollider : public Component, public PhysicsRectangle
{
public:


  static String GetType() { return "BoxCollider"; }

  virtual void Initialize() override;

  virtual void OnDestroy() override;


  virtual void PropagateTransform(const Transform2D& newTransform) override;

  virtual void Update(const float& delta) override;

  void AddCollisionEnterCallback(const CollisionCallback& c);

  void AddCollisionStayCallback(const CollisionCallback& c);

  void AddCollisionExitCallback(const CollisionCallback& c);

  void OnCollisionEnter(const PhysicsCollisionResult& collision);

  void OnCollisionStay(const PhysicsCollisionResult& collision);
  
  void OnCollisionExit(const PhysicsCollisionResult& collision);

  virtual void collisionCallback(PhysicsCollisionResult& collision) override
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
      m_collisions.push_back(new PhysicsCollisionResult(collision));
      OnCollisionEnter(collision);
    }
  }

  virtual void updateCallback(unsigned int deltaMs) override
  {
    int i = 0;
    // for (const SharedPtr<PhysicsCollisionResult>& obj : m_collisions)
    for (const PhysicsCollisionResult* obj : m_collisions)
    {
      // if (!obj) 
      // { 
      //   continue;
      // }
      
      // if (!obj->object1.collideWith(obj->object2).hasCollided)
      if (!obj->object1.collideWith(obj->object2).hasCollided)
      {
        // OnCollisionExit(*obj.get());
        OnCollisionExit(*obj);
        m_collisions.erase(m_collisions.begin() + i);
      }
      ++i;
    }
  }

  void UnregisterCollisionResult()
  {
    // int i = 0;
    // // for (SharedPtr<PhysicsCollisionResult>& obj : m_collisions)
    // for (const PhysicsCollisionResult* obj : m_collisions)
    // {
    //   // if (obj.get() == nullptr || !obj)
    //   // {
    //   //   continue;
    //   // }
    // 
    //   // if (obj->object2 == bodyToFind)
    //   if ( obj->object2 == this)
    //   {
    //     m_collisions.erase(m_collisions.begin() + i);
    //   }
    //   ++i;
    // }
  }

  // Vector<SharedPtr<PhysicsCollisionResult>> m_collisions;

  Vector<PhysicsCollisionResult*> m_collisions;

  Vector<CollisionCallback> m_onCollisionEnterCallbackList;
  Vector<CollisionCallback> m_onCollisionStayCallbackList;
  Vector<CollisionCallback> m_onCollisionExitCallbackList;
  // sfp::AABB* m_box;
};

