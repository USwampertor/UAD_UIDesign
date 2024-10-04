#pragma once

#include "uiPrerequisites.h"
#include "uiComponent.h"

#include <SFML/Graphics/View.hpp>

using FloatRect = sf::FloatRect;
using View = sf::View;

class Camera : public Component, View
{
public:

  static eCOMPONENTTYPE GetType() { return eCOMPONENTTYPE::CAMERA; }

  Camera() = default;

  ~Camera() = default;

  Camera(const Vector2f& pos, const Vector2f& s) : View(pos, s) {}

  Camera(const FloatRect& rect) : View(rect) {}

  virtual void Initialize() override;

  virtual void OnDestroy() override;

  virtual void PropagateTransform(const Transform2D& newTransform) override;

  virtual void Update(const float& delta) override;

};

