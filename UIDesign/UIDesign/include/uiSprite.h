#pragma once

#include "uiPrerequisites.h"

#include "uiComponent.h"
#include "uiTexture.h"

#include <SFML/Graphics/Sprite.hpp>

class Sprite : public Component, public sf::Sprite 
{
public:

  Sprite() = default;
  Sprite(Texture t) : sf::Sprite(static_cast<sf::Texture>(t)) {}
  ~Sprite() = default;

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
