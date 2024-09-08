#pragma once

#include "uiPrerequisites.h"
#include "uiComponent.h"

#include <SFML/Graphics/View.hpp>

class Camera : public Component, sf::View
{
  Camera() = default;

  Camera(const Vector2f& pos, const Vector2f& s)
  {
    sf::View(pos, s);
  }

  virtual void Initialize() override
  {

  }

};

