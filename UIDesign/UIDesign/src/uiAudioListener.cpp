#include "uiAudioListener.h"

#include "uiEntity.h"

void AudioListener::PropagateTransform(const Transform2D& newTransform)
{
  Listener::setPosition(newTransform.position.x + m_offset->position.x,
                        newTransform.position.y + m_offset->position.y,
                        5.0f);
}

void AudioListener::Initialize()
{
  m_offset->Reset();
  Listener::setPosition(m_parent->GetTransform().position.x + m_offset->position.x,
                        m_parent->GetTransform().position.y + m_offset->position.y,
                        5.0f);
}

void AudioListener::OnDestroy()
{

}

void AudioListener::Update(const float& delta)
{
}

void AudioListener::SetVolume(const float& newValue)
{
  Listener::setGlobalVolume(newValue);
}

const float& AudioListener::GetVolume()
{
  return Listener::getGlobalVolume();
}
