#pragma once
#include "uiPrerequisites.h"

#include "uiResource.h"

#include <SFML/Graphics/Font.hpp>

class Font : public Resource, public sf::Font
{
  static eRESOURCETYPE GetType() { return (eRESOURCETYPE::FONT); }
};