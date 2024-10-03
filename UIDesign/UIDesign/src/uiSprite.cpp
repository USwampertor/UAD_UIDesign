#include "uiSprite.h"

#include <iostream>

void Sprite::Initialize()
{
  setOrigin(getLocalBounds().width / 2, getLocalBounds().height / 2);
}
void Sprite::OnDestroy()
{

}
void Sprite::PropagateTransform(const Transform2D& newTransform)
{
  setOrigin(getLocalBounds().width / 2, getLocalBounds().height / 2);
  Vector2f scale = { newTransform.scale.x * m_offset->scale.x ,
                     newTransform.scale.y * m_offset->scale.y };
  setPosition(newTransform.position + m_offset->position);
  setScale(scale);
  setRotation(newTransform.rotation + m_offset->rotation);
}
void Sprite::Update(const float& delta)
{

}

void Sprite::Flip()
{
  m_flippedX = !m_flippedX;
  m_offset->scale.x = -m_offset->scale.x;
}

void Sprite::FlipX(const bool& toFlip)
{
  m_flippedX = toFlip;
  m_offset->scale.x = std::abs(m_offset->scale.x) * m_flippedX ? -1 : 1;
}

void Sprite::FlipY(const bool& toFlip)
{
  m_flippedY = toFlip;
  m_offset->scale.y = std::abs(m_offset->scale.y) * m_flippedY ? -1 : 1;
}
