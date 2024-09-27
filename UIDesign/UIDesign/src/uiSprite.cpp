#include "uiSprite.h"

#include <iostream>

void Sprite::Initialize()
{

}
void Sprite::OnDestroy()
{

}
void Sprite::PropagateTransform(const Transform2D& newTransform)
{
  setOrigin(Vector2f(getTextureRect().width / 2, getTextureRect().width / 2));
  // Vector2f cornerOffset(getTexture()->getSize().x / 2, getTexture()->getSize().y / 2);
  setPosition(newTransform.position + m_offset->position);//- cornerOffset);
  Vector2f scale = { newTransform.scale.x * m_offset->scale.x ,
                     newTransform.scale.y * m_offset->scale.y };
  setScale(scale);
  setRotation(newTransform.rotation + m_offset->rotation);
  // setOrigin(Vector2f(0.5f, 0.5f));
}
void Sprite::Update(const float& delta)
{

}

void Sprite::Flip()
{
  m_flippedX = !m_flippedX;
  m_offset->scale.x = -m_offset->scale.x;
}
