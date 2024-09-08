#pragma once

#include "uiPrerequisites.h"

#include "uiUtilities.h"
#include "uiComponent.h"

#include <SFPhysics/SFPhysics.h>

#include <iostream>

using CollisionCallback = Callback<void, const sfp::PhysicsBodyCollisionResult&>;
using PhysicsCollisionResult =  sfp::PhysicsBodyCollisionResult;
using PhysicsRectangle = sfp::PhysicsRectangle;

class BoxCollider : public Component, public PhysicsRectangle
{
public:
  static String GetType() { return "BoxCollider"; }

  virtual void Initialize() override
  {
    m_offset->Reset();
    setFillColor(sf::Color::Transparent);
    setOutlineColor(sf::Color::Red);
    setOutlineThickness(5);
  }

  virtual void PropagateTransform(const Transform2D& newTransform) override;

  virtual void Update(const float& delta) override;

  void AddCollisionEnterCallback(const CollisionCallback& c);

  void AddCollisionStayCallback(const CollisionCallback& c);

  void AddCollisionExitCallback(const CollisionCallback& c);

  void OnCollisionEnter(const PhysicsCollisionResult& collision);

  void OnCollisionStay(const PhysicsCollisionResult& collision);
  
  void OnCollisionExit(const PhysicsCollisionResult& collision);

  virtual void collisionCallback(PhysicsCollisionResult& collision)
  {
    
  }

  // virtual void updateCallback(unsigned int deltaMs) override;


  Vector<CollisionCallback> onCollisionEnterCallbackList;
  Vector<CollisionCallback> onCollisionStayCallbackList;
  Vector<CollisionCallback> onCollisionExitCallbackList;
  // sfp::AABB* m_box;
};

