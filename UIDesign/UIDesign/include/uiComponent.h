#pragma once
#include "uiUtilities.h"

struct Transform2D
{
public:


public:
  sf::Vector2f position;
  sf::Vector2f scale;
  float rotation;
};


virtual class Component
{
public:
  virtual void PropagateTransform(Transform2D* newTransform) = 0;

  virtual void Update(float delta) = 0;

  virtual String GetType() = 0;

  virtual void Initialize() = 0;
};