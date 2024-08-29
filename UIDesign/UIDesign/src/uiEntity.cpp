#include "uiEntity.h"

void Entity::PropagateTransform()
{
  for (auto& [key, component] : m_components)
  {
    component->PropagateTransform(GetTransform());
  }
}

void Entity::Move(const sf::Vector2f& delta)
{
  m_transform->position += delta;
  PropagateTransform();
}

void Entity::Scale(const sf::Vector2f& delta)
{
  m_transform->scale += delta;
  PropagateTransform();
}

void Entity::Rotate(const float& delta)
{
  m_transform->rotation += delta;
  PropagateTransform();
}

void Entity::SetPosition(const sf::Vector2f& newPosition)
{
  m_transform->position = newPosition;
  PropagateTransform();
}

void Entity::SetScale(const sf::Vector2f& newScale)
{
  m_transform->scale = newScale;
  PropagateTransform();
}

void Entity::SetRotation(const float& newRotation)
{
  m_transform->rotation = newRotation;
  PropagateTransform();
}


