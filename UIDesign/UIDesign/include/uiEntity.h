/**
 * Entity class
 */
#pragma once

#include "uiAnimation.h"
#include "uiAnimator.h"

#include <SFML/Main.hpp>
#include <SFML/Graphics.hpp>

struct Transform2D
{
public:


public:
  sf::Vector2f position;
  sf::Vector2f scale;
  sf::Vector2f rotation;
};

class Entity
{
public:

  void Move(sf::Vector2f delta);

  void Scale(sf::Vector2f delta);

  void Rotate(sf::Vector2f delta);

  void SetPosition(sf::Vector2f newPosition);

  void SetRotation(sf::Vector2f newRotation);

  void SetScale(sf::Vector2f newScale);

  void Update(float delta);

  Entity() = default;

  ~Entity() = default;

  Transform2D m_transform;

  Animator* m_animator;

private:

};

