#include "uiAnimation.h"

void Animation::Initialize(Vector<SharedPtr<Texture>> newTextures, const float& duration)
{
  m_frames = newTextures;
  m_animationTime = duration;
  m_currentTime = 0;
}

void Animation::Update(const float& delta)
{
  m_currentTime += delta;
  if (m_loop && m_currentTime > m_animationTime)
  {
    m_currentTime = std::fmod(m_currentTime, m_animationTime);
  }
  m_currentTime = std::clamp(m_currentTime, 0.0f, m_animationTime - 1.0f);
}

void Animation::AddFrame(SharedPtr<Texture> newFrame)
{
  m_frames.push_back(newFrame);
}

void Animation::SetCurrentTime(const float& newValue)
{
  m_currentTime = newValue;
  if (m_loop && m_currentTime > m_animationTime)
  {
    m_currentTime = std::fmod(newValue, m_animationTime);
  }
  m_currentTime = std::clamp(m_currentTime, 0.0f, m_animationTime - 1.0f);
}

void Animation::SetLoop(const bool& ifLoop)
{
  m_loop = ifLoop;
}

SharedPtr<Texture> Animation::GetCurrentFrame()
{
  int actualFrame = std::floor((m_frames.size() * m_currentTime) / m_animationTime);
  return m_frames[actualFrame];
}


