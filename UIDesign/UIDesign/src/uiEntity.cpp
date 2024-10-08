#include "uiEntity.h"

#include "uiResourceManager.h"
#include "uiTexture.h"


JSONDocument Entity::Serialize()
{
  JSONDocument d;
  d.SetObject();
  JSONDocument::AllocatorType& allocator = d.GetAllocator();
  d.AddMember("name", m_name, allocator);
  d.AddMember("active", m_isActive, allocator);
  
  JSONValue transform(rapidjson::kObjectType);
  
  JSONValue position(rapidjson::kArrayType);
  position.PushBack(m_transform->position.x, allocator).PushBack(m_transform->position.y, allocator);
  transform.AddMember("position", position, allocator);
  JSONValue scale(rapidjson::kArrayType);
  scale.PushBack(m_transform->scale.x, allocator).PushBack(m_transform->scale.y, allocator);
  transform.AddMember("scale", scale, allocator);
  transform.AddMember("rotation", scale, allocator);

  d.AddMember("transform", transform, allocator);

  return d;
}

void Entity::Initialize()
{
  m_gizmoSprite = new Sprite();
  m_gizmoSprite->setTexture(*ResourceManager::Instance().GetResource<Texture>("gizmo"));
  m_gizmoSprite->setOrigin(m_gizmoSprite->getLocalBounds().width / 2, m_gizmoSprite->getLocalBounds().height / 2);
  m_gizmoSprite->setColor(sf::Color(255, 255, 255, 128));
  SetPosition(sf::Vector2f(0.0f, 0.0f));
  SetRotation(0.0f);
  SetScale(sf::Vector2f(1.0f, 1.0f));
}

void Entity::PropagateTransform()
{
  m_gizmoSprite->setPosition(GetTransform().position);
  for (auto& [key, component] : m_components)
  {
    component->PropagateTransform(GetTransform());
  }
}

void Entity::AttachChildren(Entity* newChild)
{
  m_children.push_back(newChild);
}

void Entity::RemoveChildren(const String& name)
{
  int i = 0;
  for (Entity* e : m_children)
  {
    if (e->GetName() == name)
    {
      m_children.erase(m_children.begin() + i);
      break;
    }
  }
}

Entity& Entity::GetChild(const String& name)
{
  int i = 0;
  for (Entity* e : m_children)
  {
    if (e->GetName() == name)
    {
      return *e;
    }
  }
}

Vector<Entity*>& Entity::GetChildren()
{
  return m_children;
}


void Entity::Move(const sf::Vector2f& delta)
{
  m_transform->position += delta;
  for (Entity* e : m_children)
  {
    e->Move(delta);
  }
  PropagateTransform();
}

void Entity::Scale(const sf::Vector2f& delta)
{
  m_transform->scale += delta;
  for (Entity* e : m_children)
  {
    e->Scale(delta);
  }
  PropagateTransform();
}

void Entity::Rotate(const float& delta)
{
  m_transform->rotation += delta;
  for (Entity* e : m_children)
  {
    e->Rotate(delta);
  }
  PropagateTransform();
}

void Entity::SetPosition(const sf::Vector2f& newPosition)
{
  m_transform->position = newPosition;
  for (Entity* e : m_children)
  {
    e->Move(newPosition);
  }
  PropagateTransform();
}

void Entity::SetScale(const sf::Vector2f& newScale)
{
  m_transform->scale = newScale;
  for (Entity* e : m_children)
  {
    e->Scale(newScale);
  }
  PropagateTransform();
}

void Entity::SetRotation(const float& newRotation)
{
  m_transform->rotation = newRotation;
  for (Entity* e : m_children)
  {
    e->Rotate(newRotation);
  }
  PropagateTransform();
}


