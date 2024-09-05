#pragma once

#include "uiPrerequisites.h"
#include "uiAnimation.h"
#include "uiComponent.h"
#include "uiUtilities.h"

#include <SFML/Graphics.hpp>


enum eANIMATIONSTATE : uint32
{
  STOPPED = 0,
  PLAYING = 1,
  PAUSED  = 2
};

class Animator : public Component
{
public:
  static String GetType() { return "Animator"; }

  Animator()
  {
    m_state = eANIMATIONSTATE::STOPPED;
    m_sprite = MakeUniqueObject<sf::Sprite>();
    m_sprite->setOrigin(Vector2f(0.5f, 0.5f));
    m_offset->Reset();
  }

  virtual void Initialize() override 
  {
  }
  
  virtual void PropagateTransform(const Transform2D& newTransform) override;

  virtual void Update(const float& delta) override;
  
  void AddAnimation(SharedPtr<Animation> newAnimation, const String& newName);

  void SetAnimation(const String& animationKey);

  void SetCurrentTime(const float& newValue);

  void SetLoop(const String& animationKey, const bool& ifLoop);

  void Play();

  void Pause();

  void Stop();

  void Flip();

  const eANIMATIONSTATE& GetState();

  sf::Sprite& GetSprite();

  Map<String, SharedPtr<Animation>> m_animations;

  UniquePtr<sf::Sprite> m_sprite;

  SharedPtr<Animation> m_currentAnimation;

private:

  float m_currentTime;

  eANIMATIONSTATE m_state;

};
