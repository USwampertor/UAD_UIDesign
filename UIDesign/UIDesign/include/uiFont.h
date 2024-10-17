#pragma once
#include "uiPrerequisites.h"

#include "uiResource.h"

#include <SFML/Graphics/Font.hpp>

class Font : public Resource, public sf::Font
{
public:
  Font() : Resource(Font::StaticType()) {}
  static eRESOURCETYPE StaticType() { return (eRESOURCETYPE::FONT); }
};