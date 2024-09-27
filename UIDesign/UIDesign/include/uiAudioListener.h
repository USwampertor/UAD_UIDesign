#pragma once
#include "uiPrerequisites.h"

#include "uiComponent.h"
#include "uiUtilities.h"

#include <SFML/Audio/Listener.hpp>

using Listener = sf::Listener;

class AudioListener : public Component
{
public:

  AudioListener() = default;

  ~AudioListener() = default;

  static eCOMPONENTTYPE GetType() { return eCOMPONENTTYPE::AUDIOLISTENER; }

  virtual void PropagateTransform(const Transform2D& newTransform) override;

  virtual void Initialize() override;

  virtual void OnDestroy() override;

  virtual void Update(const float& delta) override;

  void SetVolume(const float& newValue);

  const float& GetVolume();
};

