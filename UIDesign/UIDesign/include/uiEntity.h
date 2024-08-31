/**
 * Entity class
 */
#pragma once

#include "uiAnimation.h"
#include "uiAnimator.h"
#include "uiComponent.h"
#include "uiUtilities.h"

#include <SFML/Main.hpp>
#include <SFML/Graphics.hpp>

class Entity
{
public:

  Entity()
  {
    m_transform = MakeUniqueObject<Transform2D>();
    m_components.clear();
    m_children.clear();
  }

  ~Entity() = default;

  template <typename T, typename = std::enable_if_t<std::is_base_of<Component, T>::value>>
  void AddComponent(SharedPtr<T> newComponent)
  {
    if (m_components.find(T::GetType()) == m_components.end())
    {
      // m_components.insert(Utils::MakePair(T::GetType(), newComponent));
    }
  }

  template <typename T, typename = std::enable_if_t<std::is_base_of<Component, T>::value>>
  SharedPtr<T> GetComponent()
  {
    if (m_components.find(T::GetType()) != m_components.end())
    {
      return REINTERPRETPOINTER(T, m_components.at(T::GetType()));
    
      // auto it = m_components.find(T::GetType());
      // return REINTERPRETPOINTER(it->second.get());
    }
  }

  template <typename T, typename = std::enable_if_t<std::is_base_of<Component, T>::value>>
  void RemoveComponent()
  {
    if (m_components.find(T::GetType()) != m_components.end())
    {
      m_components.erase(T::GetType());
    }
  }
  //
  template <typename T, 
            typename = std::enable_if_t<std::is_base_of<Component, T>::value>, 
            typename ... Args>
  SharedPtr<T> CreateComponent(Args ... args)
  {
    if (m_components.find(T::GetType()) == m_components.end())
    {
      m_components.insert(Utils::MakePair(T::GetType(), MakeSharedObject<T>()));
      m_components.at(T::GetType())->Initialize(args ...);
      // return REINTERPRETPOINTER(T*, *m_components[T::GetType()].get());
      return REINTERPRETPOINTER(T, m_components.at(T::GetType()));
    }
  }

  virtual void Initialize()
  {
    SetPosition(sf::Vector2f(0.0f, 0.0f));
    SetRotation(0.0f);
    SetScale(sf::Vector2f(1.0f, 1.0f));
  }

  virtual void Update(const float& delta)
  {
    for (auto& [key, component] : m_components)
    {
      component->Update(delta);
    }
  }

  Transform2D& GetTransform()
  {
    return *m_transform;
  }

  Vector<UniquePtr<Entity>>& Children()
  {
    return m_children;
  }


  void Destroy();

  void Move(const sf::Vector2f& delta);

  void Scale(const sf::Vector2f& delta);

  void Rotate(const float& delta);

  void SetPosition(const sf::Vector2f& newPosition);

  void SetScale(const sf::Vector2f& newScale);

  void SetRotation(const float& newRotation);

private:

  void PropagateTransform();

protected:

  UniquePtr<Transform2D> m_transform;

public:

  Map<String, SharedPtr<Component>> m_components;

  Vector<UniquePtr<Entity>> m_children;
};
