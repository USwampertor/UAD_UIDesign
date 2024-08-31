#pragma once

#include "uiResource.h"
#include "uiUtilities.h"

#include <SFML/Graphics.hpp>

class Texture : public Resource, public sf::Texture 
{
public:
  static eRESOURCETYPE GetType() { return eRESOURCETYPE::TEXTURE; }
};