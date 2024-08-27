#pragma once

#include "uiUtilities.h";
#include "uiAnimation.h"

#include <SFML/Graphics.hpp>


class Animator
{
public:
  void AddAnimation(Animation* newAnimation, String newName);

  sf::Sprite* GetSprite();

  Map<String, Animation*> m_animations;

  sf::Sprite* m_sprite;

};

