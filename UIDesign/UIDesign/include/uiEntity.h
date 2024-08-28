/**
 * Entity class
 */
#pragma once

#include "uiAnimation.h"
#include "uiAnimator.h"
#include "uiComponent.h"

#include <SFML/Main.hpp>
#include <SFML/Graphics.hpp>


class Entity
{
public:

  void AddComponent(Component* newComponent);

  //template <typename T = Component*>
  //void RemoveComponent<T>();
  //
  //template <typename T>
  //void CreateComponent<T>();

  void Initialize();

  Component* GetComponent(String type);

  void Move(sf::Vector2f delta);

  void Scale(sf::Vector2f delta);

  void Rotate(float delta);

  void SetPosition(sf::Vector2f newPosition);

  void SetRotation(float newRotation);

  void SetScale(sf::Vector2f newScale);

  void Update(float delta);

  void PropagateTransform();

  Entity() = default;

  ~Entity() = default;

  Transform2D m_transform;

  Vector<Component*> m_components;

private:

};

