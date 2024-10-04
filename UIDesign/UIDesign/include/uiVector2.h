#pragma once

#include "uiPrerequisites.h"

#include "uiMath.h"

#include <SFML/System/Vector2.hpp>

using Vector2f = sf::Vector2f;

using Vector2i = sf::Vector2i;

template <typename T>
using Vector2 = sf::Vector2<T>;


template<typename T>
struct Vec2Math
{
  static sf::Vector2<T> Normal(const sf::Vector2<T>& a)
  {
    const double length = Length(a);
    const double newX = a.x / length;
    const double newY = a.y / length;

    return sf::Vector2<T>(newX, newY);
  }

  static T Length(const sf::Vector2<T>& a)
  {
    return Math::Sqrt(Math::Sqr(a.x) + Math::Sqr(a.y));

  }

  static sf::Vector2<T> Inverted(const sf::Vector2<T>& a)

  {
    return sf::Vector2<T>(-a.x, -a.y);
  }

  static sf::Vector2<T> Times(const sf::Vector2<T>& a, const float& times)
  {
    const auto newX = a.x * times;
    const auto newY = a.y * times;

    return sf::Vector2<T>(newX, newY);
  }
};