#include "uiBoxCollider.h"

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

