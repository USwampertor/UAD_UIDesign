#pragma once

#include "uiPrerequisites.h"

#include "uiUtilities.h"
#include "uiComponent.h"

#include <SFPhysics/SFPhysics.h>


class BoxCollider : public Component, public sfp::PhysicsRectangle
{
public:
  static String GetType() { return "BoxCollider"; }

  virtual void Initialize() override
  {
    // m_box = new sf::RectangleShape();
    // m_box->setSize(Vector2f(1.0f, 1.0f));
    // m_box->setOrigin(Vector2f(0.5f, 0.5f));
    // m_box->setPosition(Vector2f(0.0f, 0.0f));
    m_offset->Reset();
    // m_box = new sfp::AABB(Vector2f(0, 0), Vector2f(1, 1));
  }

  virtual void PropagateTransform(const Transform2D& newTransform) override;

  virtual void Update(const float& delta) override;

  // virtual void collisionCallback(sfp::PhysicsBodyCollisionResult& collision) override;
  // 
  // virtual void updateCallback(unsigned int deltaMs) override;


  Vector<Callback<void, const sfp::PhysicsBodyCollisionResult&>> onCollisionCallbackList;
  // sfp::AABB* m_box;
};

