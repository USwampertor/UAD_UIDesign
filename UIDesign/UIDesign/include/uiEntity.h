/**
 * Entity class
 */
#pragma once

#include "uiPrerequisites.h"

#include "uiComponent.h"
#include "uiJSON.h"
#include "uiUtilities.h"
#include "uiVector2.h"

#include "uiSprite.h"


class Entity
{
public:

  static String GetType() { assert(true && "IMPLEMENT THIS"); return "Entity"; }

  Entity()
  {
    m_transform = MakeUniqueObject<Transform2D>();
    m_components.clear();
    m_children.clear();
    m_isActive = true;
  }

  Entity(const String& newName)
  {
    m_transform = MakeUniqueObject<Transform2D>();
    m_components.clear();
    m_children.clear();
    m_name = newName;
    m_isActive = true;
  }

  Entity(Entity&) = default;

  ~Entity() = default;

  template <typename T, typename = std::enable_if_t<std::is_base_of<Component, T>::value>>
  void AddComponent(SharedPtr<T>& newComponent)
  {
    if (m_components.find(T::GetType()) == m_components.end())
    {
      newComponent->m_parent = this;
      m_components.insert(Utils::MakePair(T::GetType(), newComponent));
    }
  }

  template <typename T, typename = std::enable_if_t<std::is_base_of<Component, T>::value>>
  T* GetComponent()
  {
    if (m_components.find(T::GetType()) != m_components.end())
    {
      return REINTERPRETPOINTER(T, m_components.at(T::GetType())).get();
    }
    return nullptr;
  }

  template <typename T, typename = std::enable_if_t<std::is_base_of<Component, T>::value>>
  void RemoveComponent()
  {
    if (m_components.find(T::GetType()) != m_components.end())
    {
      m_components.at(T::GetType())->m_parent = nullptr;
      m_components.erase(T::GetType());
    }
  }
  //
  template <typename T, 
            typename = std::enable_if_t<std::is_base_of<Component, T>::value>, 
            typename ... Args>
  T* CreateComponent(Args ... args)
  {
    if (m_components.find(T::GetType()) == m_components.end())
    {

      // Special case for animator since this has to create a Sprite component
      if (eCOMPONENTTYPE::ANIMATOR == T::GetType() && 
          m_components.find(eCOMPONENTTYPE::SPRITE) == m_components.end())
      {
        CreateComponent<Sprite>();
      }

      m_components.insert(Utils::MakePair(T::GetType(), MakeSharedObject<T>(args ...)));
      m_components.at(T::GetType())->m_parent = this;
      m_components.at(T::GetType())->Initialize();
    }
    return REINTERPRETPOINTER(T, m_components.at(T::GetType())).get();

  }

  virtual void Deserialize(const JSONDocument& doc) {}

  virtual JSONDocument Serialize();

  virtual void OnInitialize() {}

  virtual void OnDestroy() 
  {
    m_children.clear();
    for (auto& [key, component] : m_components)
    {
      component->OnDestroy();
    }
  }

  virtual void Initialize();

  void SetActive(bool isActive)
  {
    m_isActive = isActive;
  }

  const bool& IsActive()
  {
    return m_isActive;
  }

  virtual void Update(const float& delta)
  {
    if (m_isActive)
    {
      for (auto& [key, component] : m_components)
      {
        component->Update(delta);
      }
    }
  }

  Transform2D& GetTransform()
  {
    return *m_transform;
  }

  const String& GetName()
  {
    return m_name;
  }

  void SetName(const String& newName)
  {
    m_name = newName;
  }

  void AttachChildren(Entity* newChild);

  void RemoveChildren(const String& name);

  Entity& GetChild(const String& name);

  Vector<Entity*>& GetChildren();

  void Move(const Vector2f& delta);

  void Scale(const Vector2f& delta);

  void Rotate(const float& delta);

  void SetPosition(const Vector2f& newPosition);

  void SetScale(const Vector2f& newScale);

  void SetRotation(const float& newRotation);

  bool m_markedToDestroy = false;

  Sprite* m_gizmoSprite;

private:

  void PropagateTransform();

protected:

  UniquePtr<Transform2D> m_transform;

private:

  String m_name;

  Map<eCOMPONENTTYPE, SharedPtr<Component>> m_components;

  Vector<Entity*> m_children;

  bool m_isActive = true;

};
