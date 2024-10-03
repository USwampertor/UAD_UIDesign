#pragma once

#include "uiPrerequisites.h"

#include "uiComponent.h"
#include "uiUtilities.h"

#include <SFML/Graphics.hpp>

class Sprite : public Component, public sf::Sprite 
{
public:
  virtual void Initialize() override;
  virtual void OnDestroy() override;
  virtual void PropagateTransform(const Transform2D& newTransform) override;
  virtual void Update(const float& delta) override;
  void Flip();
  void FlipX(const bool& toFlip);
  void FlipY(const bool& toFlip);
  bool m_flippedX = false;
  bool m_flippedY = false;
};
