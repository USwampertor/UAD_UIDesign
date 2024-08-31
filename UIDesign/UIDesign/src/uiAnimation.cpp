#include "uiAnimation.h"

void Animation::Initialize(Vector<SharedPtr<Texture>> newTextures, const float& duration)
{
  m_frames = newTextures;
  m_animationTime = duration;
  // m_currentTime = 0;
}

void Animation::AddFrame(SharedPtr<Texture> newFrame)
{
  m_frames.push_back(newFrame);
}

void Animation::SetLoop(const bool& ifLoop)
{
  m_loop = ifLoop;
}

SharedPtr<Texture> Animation::GetCurrentFrame(const float& currentTime)
{
  int actualFrame = std::floor((m_frames.size() * currentTime) / m_animationTime);
  return m_frames[actualFrame];
}


