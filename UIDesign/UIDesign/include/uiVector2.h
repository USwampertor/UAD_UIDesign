#pragma once

#include "uiPrerequisites.h"

#include "uiMath.h"

#include <SFML/System/Vector2.hpp>

using Vector2f = sf::Vector2f;

using Vector2i = sf::Vector2i;

template <typename T>
using Vector2 = sf::Vector2<T>;


struct Vec2
{
  template<typename T>
  static Vector2<T> Normal(const Vector2<T>& a)
  {
    const T length = Length(a);
    const T newX = a.x / length;
    const T newY = a.y / length;

    return sf::Vector2<T>(newX, newY);
  }

  template<typename T>
  static T Length(const Vector2<T>& a)
  {
    return Math::Sqrt(Math::Sqr(a.x) + Math::Sqr(a.y));

  }

  template<typename T>
  static T SqrLength(const Vector2<T>& a)
  {
    return Math::Sqr(a.x) + Math::Sqr(a.y);

  }

  template<typename T>
  static Vector2<T> Inverted(const Vector2<T>& a)

  {
    return Vector2<T>(-a.x, -a.y);
  }

  template<typename T>
  static Vector2<T> Times(const Vector2<T>& a, const float& times)
  {
    const auto newX = a.x * times;
    const auto newY = a.y * times;

    return Vector2<T>(newX, newY);
  }
};