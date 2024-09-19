#include "uiAudioSource.h"

void AudioSource::SetClip(SharedPtr<AudioClip> clip)
{
  if (eRESOURCETYPE::SOUND == m_type)
  {
    m_sound->stop();
    m_sound->setBuffer(*clip);
  }
  else if (eRESOURCETYPE::MUSIC == m_type)
  {
    m_music->stop();
    m_sound->setBuffer(*clip);
    m_type = eRESOURCETYPE::SOUND;
  }
  else
  {
    m_sound->setBuffer(*clip);
    m_type = eRESOURCETYPE::SOUND;
  }
}

void AudioSource::SetClip(SharedPtr<MusicClip> clip)
{
  if (eRESOURCETYPE::SOUND == m_type)
  {
    m_sound->stop();
    m_music = clip;
    m_type = eRESOURCETYPE::MUSIC;
  }
  else if (eRESOURCETYPE::MUSIC == m_type)
  {
    m_music->stop();
    m_music = clip;
  }
  else
  {
    m_music = clip;
    m_type = eRESOURCETYPE::SOUND;
  }
}


void AudioSource::Play()
{
  if (eRESOURCETYPE::SOUND == m_type)
  {
    m_sound->play();
  }
  else if (eRESOURCETYPE::MUSIC == m_type)
  {
    m_music->play();
  }
}

void AudioSource::PlayOnce()
{
  if (eRESOURCETYPE::SOUND == m_type)
  {
    m_sound->setLoop(false);
    m_sound->play();
  }
  else if (eRESOURCETYPE::MUSIC == m_type)
  {
    m_music->setLoop(false);
    m_music->play();
  }
}

void AudioSource::SetLoop(const bool& shouldLoop)
{
  if (eRESOURCETYPE::SOUND == m_type)
  {
    m_sound->setLoop(shouldLoop);
  }
  else if (eRESOURCETYPE::MUSIC == m_type)
  {
    m_music->setLoop(shouldLoop);
  }
}

void AudioSource::Pause()
{
  if (eRESOURCETYPE::SOUND == m_type)
  {
    m_sound->pause();
  }
  else if (eRESOURCETYPE::MUSIC == m_type)
  {
    m_music->pause();
  }
}

void AudioSource::SetVolume(const float& newVolume)
{
  if (eRESOURCETYPE::SOUND == m_type)
  {
    m_sound->setVolume(newVolume);
  }
  else if (eRESOURCETYPE::MUSIC == m_type)
  {
    m_music->setVolume(newVolume);
  }
}

const float& AudioSource::GetVolume()
{
  if (eRESOURCETYPE::SOUND == m_type)
  {
    return m_sound->getVolume();
  }
  else if (eRESOURCETYPE::MUSIC == m_type)
  {
    return m_music->getVolume();
  }
}

void AudioSource::PropagateTransform(const Transform2D& newTransform)
{
  Vector3f newPosition(newTransform.position.x + m_offset->position.x,
                       0.0f,
                       newTransform.position.y + m_offset->position.y);
  m_music->setPosition(newPosition);
  m_sound->setPosition(newPosition);
}




