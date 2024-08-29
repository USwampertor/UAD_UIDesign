#include "uiAnimator.h"

void Animator::PropagateTransform(const Transform2D& newTransform)
{
  m_sprite->setPosition(newTransform.position + m_offset->position);
  Vector2f scale = { newTransform.scale.x * m_offset->scale.x ,
                     newTransform.scale.y * m_offset->scale.y };
  m_sprite->setScale(scale);
  m_sprite->setRotation(newTransform.rotation + m_offset->rotation);
}

void Animator::Update(const float& delta)
{
  if (m_state == eANIMATIONSTATE::PLAYING)
  {
    m_currentAnimation->Update(delta);
    m_sprite->setTexture(*m_currentAnimation->GetCurrentFrame());
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
    m_currentAnimation = m_animations.at(animationKey);
  }
}

void Animator::SetCurrentTime(const float& newValue)
{
  m_currentAnimation->SetCurrentTime(newValue);
  m_sprite->setTexture(*m_currentAnimation->GetCurrentFrame());
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


