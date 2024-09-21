#pragma once

#include "uiPrerequisites.h"
#include "uiUtilities.h"

#include "uiModule.h"

#include <SFML/Graphics/RenderWindow.hpp>

#include "uiGameSettings.h"

using RenderWindow = sf::RenderWindow;

class WindowManager : public Module<WindowManager>
{
public:
  virtual void OnStartUp()
  {

  }

  void Clear();

  void Display();

  void Initialize(const GameSettings& gameSettings);


  SharedPtr<RenderWindow> m_mainWindow;
};

