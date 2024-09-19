#include "uiBoxCollider.h"

#include "uiPhysics.h"

void BoxCollider::PropagateTransform(const Transform2D& newTransform)
{
  Vector2f newPosition = newTransform.position + m_offset->position;
  // m_box->setPosition(newTransform->position + m_offset.position);
  // Vector2f scale = { newTransform->scale.x * m_offset.scale.x ,
  //                    newTransform->scale.y * m_offset.scale.y };
  // m_box->setScale(scale);
  // m_box->setRotation(newTransform->rotation + m_offset.rotation);
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




