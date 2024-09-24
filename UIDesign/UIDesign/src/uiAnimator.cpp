#include "uiAnimator.h"

#include "uiSprite.h"
#include "uiEntity.h"

void Animator::Initialize()
{
  if (m_parent == nullptr)
  {
    // Send error
  }
  else
  {
    m_sprite = m_parent->GetComponent<Sprite>();
  }
}

void Animator::PropagateTransform(const Transform2D& newTransform)
{
  
}

void Animator::Update(const float& delta)
{
  if (m_state == eANIMATIONSTATE::PLAYING && m_currentAnimation != nullptr)
  {
    // m_currentAnimation->Update(delta);

    m_currentTime += delta;
    if (m_currentAnimation->m_loop && m_currentTime > m_currentAnimation->m_animationTime)
    {
      m_currentTime = std::fmod(m_currentTime, m_currentAnimation->m_animationTime);
    }
    m_currentTime = std::clamp(m_currentTime, 0.0f, m_currentAnimation->m_animationTime - 0.1f);

    m_sprite->setTexture(*m_currentAnimation->GetCurrentFrame(m_currentTime));
  }
}

void Animator::AddAnimation(SharedPtr<Animation> newAnimation, const String& newName)
{
  m_animations.insert(Utils::MakePair(newName, newAnimation));
}

void Animator::SetAnimation(const String& animationKey)
{
  if (m_animations.find(animationKey) != m_animations.end())
  {
    m_animationName = animationKey;
    m_currentAnimation = m_animations.at(animationKey);
    m_sprite->setTexture(*m_currentAnimation->GetCurrentFrame(m_currentTime));
  }
}

void Animator::SetCurrentTime(const float& newValue)
{
  // m_currentAnimation->SetCurrentTime(newValue);

  m_currentTime = newValue;
  if (m_currentAnimation->m_loop && m_currentTime > m_currentAnimation->m_animationTime)
  {
    m_currentTime = std::fmod(newValue, m_currentAnimation->m_animationTime);
  }
  m_currentTime = std::clamp(m_currentTime, 0.0f, m_currentAnimation->m_animationTime - 0.1f);

  m_sprite->setTexture(*m_currentAnimation->GetCurrentFrame(m_currentTime));
}

void Animator::SetLoop(const String& animationKey, const bool& ifLoop)
{
  if (m_animations.find(animationKey) != m_animations.end())
  {
    m_animations.at(animationKey)->SetLoop(ifLoop);
  }
}

void Animator::Play()
{
  m_state = eANIMATIONSTATE::PLAYING;
}

void Animator::Pause()
{
  m_state = eANIMATIONSTATE::PAUSED;
}

void Animator::Stop()
{
  m_state = eANIMATIONSTATE::STOPPED;
  SetCurrentTime(0);
}

void Animator::Flip()
{
  m_offset->scale.x = -m_offset->scale.x;
}

const eANIMATIONSTATE& Animator::GetState()
{
  return m_state;
}

sf::Sprite& Animator::GetSprite()
{
  return *m_sprite;
}


