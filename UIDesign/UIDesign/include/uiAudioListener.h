#pragma once
#include "uiPrerequisites.h"

#include "uiComponent.h"
#include "uiUtilities.h"

#include <SFML/Audio/Listener.hpp>

using Listener = sf::Listener;

class AudioListener : public Component
{
  static eCOMPONENTTYPE GetType() { return eCOMPONENTTYPE::AUDIOLISTENER; }

  virtual void PropagateTransform(const Transform2D& newTransform) override;

  void SetVolume(const float& newValue);
};

