#pragma once

#include "uiPrerequisites.h"

#include "uiResource.h"

#include <SFML/Audio/Music.hpp>


class MusicClip : public Resource, public sf::Music 
{
public:
  static eRESOURCETYPE GetType() { return eRESOURCETYPE::MUSIC; }

};

