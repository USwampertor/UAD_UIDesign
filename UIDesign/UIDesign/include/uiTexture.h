#pragma once

#include "uiPrerequisites.h"

#include "uiResource.h"
#include "uiUtilities.h"

#include <SFML/Graphics/Texture.hpp>

class Texture : public Resource, public sf::Texture 
{
public:
  static eRESOURCETYPE GetType() { return eRESOURCETYPE::TEXTURE; }
};