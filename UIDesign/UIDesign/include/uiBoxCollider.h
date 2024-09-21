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


  static eCOMPONENTTYPE GetType() { return eCOMPONENTTYPE::COLLIDER; }

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

  virtual void collisionCallback(PhysicsCollisionResult& collision) override;

  virtual void updateCallback(unsigned int deltaMs) override;

  // Vector<SharedPtr<PhysicsCollisionResult>> m_collisions;

  Vector<PhysicsCollisionResult*> m_collisions;

  Vector<CollisionCallback> m_onCollisionEnterCallbackList;
  Vector<CollisionCallback> m_onCollisionStayCallbackList;
  Vector<CollisionCallback> m_onCollisionExitCallbackList;
  // sfp::AABB* m_box;
};

