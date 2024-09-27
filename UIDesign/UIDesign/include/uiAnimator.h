#pragma once

#include "uiPrerequisites.h"
#include "uiAnimation.h"
#include "uiComponent.h"
#include "uiSprite.h"
#include "uiUtilities.h"

#include <SFML/Graphics.hpp>

BETTER_ENUM(
  eANIMATIONSTATE,
  uint32,
  STOPPED = 0,
  PLAYING = 1,
  PAUSED = 2
)

class Animator : public Component
{
public:
  static eCOMPONENTTYPE GetType() { return eCOMPONENTTYPE::ANIMATOR; }

  Animator()
  {
    m_state = eANIMATIONSTATE::STOPPED;
    
    m_offset->Reset();
    m_currentTime = 0;
  }

  virtual void Initialize() override;

  virtual void OnDestroy() override
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

  Sprite& GetSprite();

  Map<String, SharedPtr<Animation>> m_animations;

  String m_animationName = "";

  // UniquePtr<sf::Sprite> m_sprite;

  // raw reference to the actual sprite component the object has
  Sprite* m_sprite;

  SharedPtr<Animation> m_currentAnimation;

private:

  float m_currentTime;

  eANIMATIONSTATE m_state = eANIMATIONSTATE::STOPPED;

};
