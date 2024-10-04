#pragma once
#include "uiPrerequisites.h"

#include "uiVector2.h"

struct Boid
{
public:
  static Vector2f Seek(const Vector2f& start, const Vector2f& end, const float& magnitude)
  {
    Vector2f toReturn;
    toReturn = Vec2Math<float>::Normal(end - start) * magnitude;
    return toReturn;
  }

  static Vector2f Flee(const Vector2f& start, const Vector2f& end, const float& magnitude)
  {
    Vector2f toReturn;
    toReturn = Vec2Math<float>::Normal(start - end) * magnitude;
    return toReturn;
  }

  static Vector2f Approach(const Vector2f& start, const Vector2f& end, const float& magnitude, const float& threshold)
  {
    Vector2f toReturn;
    toReturn = Vec2Math<float>::Length(end - start) > threshold ? Vec2Math<float>::Normal(end - start) * magnitude : Vector2f(0,0);
    return toReturn;
  }
};