#pragma once

#include "uiPrerequisites.h"

#include "uiResource.h"

#include <SFML/Audio/SoundBuffer.hpp>


class AudioClip : public Resource, public sf::SoundBuffer 
{
public:
  static eRESOURCETYPE GetType() { return eRESOURCETYPE::SOUND; }

};

