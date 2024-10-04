#pragma once

#include "uiPrerequisites.h"

#include "uiComponent.h"
#include "uiCollision.h"
#include "uiVector2.h"

class BoxCollider : public Component, public PhysicsRectangle
{
public:

  static eCOMPONENTTYPE GetType() { return eCOMPONENTTYPE::COLLIDER; }

  virtual void Initialize() override;

  virtual void OnDestroy() override;

  virtual void PropagateTransform(const Transform2D& newTransform) override;

  virtual void Update(const float& delta) override;

  void SetSize(const Vector2f& newSize);

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

  Vector2f m_ColliderSize;
  // sfp::AABB* m_box;
};

