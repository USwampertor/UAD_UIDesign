#pragma once
#include "uiPrerequisites.h"

class Boid
{
  static Vector2f Seek(const Vector2f& start, const Vector2f& end, const float& magnitude)
  {
    Vector2f toReturn;
    toReturn = end - start;
    return toReturn;
  }

  static Vector2f Flee()
  {
    Vector2f toReturn;

    return toReturn;
  }

  static Vector2f Approach()
  {
    Vector2f toReturn;

    return toReturn;
  }
};