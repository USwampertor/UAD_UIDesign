#pragma once

#include "uiPrerequisites.h"


#include "uiAudioClip.h"
#include "uiComponent.h"
#include "uiMusicClip.h"

#include "uiResource.h"
#include "uiUtilities.h"

#include <SFML/Audio/Sound.hpp>

using Vector3f = sf::Vector3f;
using Sound = sf::Sound;

class AudioSource : public Component
{
public:

  static eCOMPONENTTYPE GetType() { return eCOMPONENTTYPE::AUDIOSOURCE; }

  AudioSource() = default;

  ~AudioSource() = default;

  AudioSource(SharedPtr<AudioClip> clip)
  {
    m_sound->setBuffer(*clip);
    m_type = eRESOURCETYPE::SOUND;
  }

  AudioSource(SharedPtr<MusicClip> clip)
  {
    m_music = clip;
    m_type = eRESOURCETYPE::MUSIC;
  }

  virtual void Initialize() override 
  {
    m_sound = MakeSharedObject<Sound>();
    m_music = MakeSharedObject<MusicClip>();
  }
  virtual void OnDestroy() override {}
  virtual void Update(const float& delta) override {}

  void SetClip(SharedPtr<AudioClip> clip);

  void SetClip(SharedPtr<MusicClip> clip);

  void Play();

  void PlayOnce();

  void SetLoop(const bool& shouldLoop);

  void Pause();

  void Stop();

  void SetVolume(const float& newVolume);

  const float& GetVolume();

  virtual void PropagateTransform(const Transform2D& newTransform) override;

  virtual void OnSetOffset() override
  {
    // if (eRESOURCETYPE::SOUND == m_type)
    // {
    //   m_sound->setPosition(Vector3f(m_offset.position.x, 0.0f, m_offset.position.y));
    // }
    // else if (eRESOURCETYPE::MUSIC == m_type)
    // {
    //   m_music->setPosition(Vector3f(m_offset.position.x, 0.0f, m_offset.position.y));
    // }
  }

private:
  
  eRESOURCETYPE m_type = eRESOURCETYPE::NONE;

  SharedPtr<MusicClip> m_music;
  SharedPtr<Sound> m_sound;
};

