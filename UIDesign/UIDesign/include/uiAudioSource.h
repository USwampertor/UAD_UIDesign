#pragma once

#include "uiPrerequisites.h"

#include "uiAudioClip.h"
#include "uiComponent.h"
#include "uiMusicClip.h"
#include "uiResource.h"

#include <SFML/Audio/Sound.hpp>

using Sound = sf::Sound;

class AudioSource : public Component
{
public:

  static eCOMPONENTTYPE GetType() { return eCOMPONENTTYPE::AUDIOSOURCE; }

  AudioSource() = default;

  ~AudioSource() = default;

  AudioSource(SharedPtr<AudioClip> clip)
  {
    m_offset->Reset();
    m_sound->setBuffer(*clip);
    m_type = eRESOURCETYPE::SOUND;
  }

  AudioSource(SharedPtr<MusicClip> clip)
  {
    m_music = clip;
    m_type = eRESOURCETYPE::MUSIC;
  }

  virtual void Initialize() override;

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

  void SetMinDistance(const float& minDistance);

  void SetAttenuation(const float& attenuation);

  void SetRelativeToListener(const bool& shouldBe);

  const float& GetVolume();

  virtual void PropagateTransform(const Transform2D& newTransform) override;

  virtual void OnSetOffset() override { }
  
  eRESOURCETYPE m_type = eRESOURCETYPE::NONE;

  SharedPtr<MusicClip> m_music;
  SharedPtr<Sound> m_sound;

private:
};

