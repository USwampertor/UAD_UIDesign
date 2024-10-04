#pragma once

#include "uiPrerequisites.h"

#include "uiResource.h"

#include <SFML/Audio/Music.hpp>

using Music = sf::Music;

class MusicClip : public Resource, public Music 
{
public:
  static eRESOURCETYPE GetType() { return eRESOURCETYPE::MUSIC; }
};

