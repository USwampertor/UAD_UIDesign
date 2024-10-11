#pragma once
#include "uiPrerequisites.h"
#include "uiComponent.h"

#include "SFML/Graphics/Shader.hpp"

class Shader : public Component, public sf::Shader
{
  static eCOMPONENTTYPE GetType() { return eCOMPONENTTYPE::SHADER; }
};

