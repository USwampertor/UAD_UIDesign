#pragma once

#include "uiPrerequisites.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/WindowBase.hpp>
#include <SFML/Window/Window.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/WindowStyle.hpp>

using RenderWindow = sf::RenderWindow;

using Window = sf::Window;

using WindowBase = sf::WindowBase;

using VideoMode = sf::VideoMode;

BETTER_ENUM(
  eWINDOWSTYLE, 
  uint32,
  NONE        = 0,
  TITLEBAR    = 1 << 0,
  RESIZE      = 1 << 1,
  CLOSE       = 1 << 2,
  FULLSCREEN  = 1 << 3,
  DEFAULT     = 1 << 0 | 1 << 1 | 1 << 2
)