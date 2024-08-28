#pragma once

#include "uiAnimation.h"
#include "uiComponent.h"
#include "uiUtilities.h";

#include <SFML/Graphics.hpp>

enum eANIMATIONSTATE : int
{
  PLAYING = 0,
  PAUSED = 1,
  STOPPED = 2
};

class Animator : public Component
{
public:
  void AddAnimation(Animation* newAnimation, String newName);

  void SetAnimation(String animationKey);

  virtual void Update(float delta) override;

  void SetCurrentTime(float newValue);

  void SetLoop(String animationKey, bool ifLoop);

  void Play();

  void Pause();

  void Stop();

  virtual String GetType() override { return "Animator"; }

  virtual void Initialize() override 
  {
    m_sprite = new sf::Sprite();
    m_state = eANIMATIONSTATE::STOPPED;
    m_sprite->setOrigin(sf::Vector2f(0.5f, 0.5f));
  }

  sf::Sprite* GetSprite();

  Map<String, Animation*> m_animations;

  sf::Sprite* m_sprite;

  Animation* m_currentAnimation;

  eANIMATIONSTATE m_state;

  virtual void PropagateTransform(Transform2D* newTransform) override;

};

