#pragma once

#include "uiPrerequisites.h"

#include "uiResource.h"

#include <SFML/Audio/Music.hpp>

using Music = sf::Music;

class MusicClip : public Resource, public Music 
{
public:
  MusicClip() : Resource(MusicClip::StaticType()) {}
  static eRESOURCETYPE StaticType() { return eRESOURCETYPE::MUSIC; }
};

