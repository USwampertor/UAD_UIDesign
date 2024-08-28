#include "uiAnimator.h"

void Animator::PropagateTransform(Transform2D* newTransform)
{
  m_sprite->setPosition(newTransform->position);
  m_sprite->setScale(newTransform->scale);
  m_sprite->setRotation(newTransform->rotation);
}

void Animator::AddAnimation(Animation* newAnimation, String newName)
{
  m_animations.insert(Utils::makePair(newName, newAnimation));
}

void Animator::SetAnimation(String animationKey)
{
  if (m_animations.find(animationKey) != m_animations.end())
  {
    m_currentAnimation = m_animations.at(animationKey);
  }
}

void Animator::Update(float delta)
{
  if (m_state == eANIMATIONSTATE::PLAYING)
  {
    m_currentAnimation->Update(delta);
    m_sprite->setTexture(*m_currentAnimation->GetCurrentFrame());
  }
}

void Animator::SetCurrentTime(float newValue)
{
  m_currentAnimation->SetCurrentTime(newValue);
  m_sprite->setTexture(*m_currentAnimation->GetCurrentFrame());
}

void Animator::SetLoop(String animationKey, bool ifLoop)
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

sf::Sprite* Animator::GetSprite()
{
  return m_sprite;
}


