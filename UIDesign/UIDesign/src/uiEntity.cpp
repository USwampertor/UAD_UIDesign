#include "uiEntity.h"

void Entity::Initialize()
{
  SetPosition(sf::Vector2f(0.0f, 0.0f));
  SetRotation(0.0f);
  SetScale(sf::Vector2f(1.0f, 1.0f));
}

void Entity::AddComponent(Component* newComponent)
{
  m_components.push_back(newComponent);
}

void Entity::PropagateTransform()
{
  for (auto& component : m_components)
  {
    component->PropagateTransform(&m_transform);
  }
}

Component* Entity::GetComponent(String type)
{
  for (auto& component : m_components)
  {
    if (type == component->GetType()) { return component; }
  }
}



void Entity::Update(float delta)
{
  for (auto& component : m_components)
  {
    component->Update(delta);
  }
}

void Entity::Move(sf::Vector2f delta)
{
  m_transform.position += delta;
  PropagateTransform();
}

void Entity::Scale(sf::Vector2f delta)
{
  m_transform.scale += delta;
  PropagateTransform();
}

void Entity::Rotate(float delta)
{
  m_transform.rotation += delta;
  PropagateTransform();
}

void Entity::SetPosition(sf::Vector2f newPosition)
{
  m_transform.position = newPosition;
  PropagateTransform();
}

void Entity::SetRotation(float newRotation)
{
  m_transform.rotation = newRotation;
  PropagateTransform();
}

void Entity::SetScale(sf::Vector2f newScale)
{
  m_transform.scale = newScale;
  PropagateTransform();
}


