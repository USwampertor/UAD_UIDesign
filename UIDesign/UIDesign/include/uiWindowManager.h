#pragma once

#include "uiPrerequisites.h"
#include "uiUtilities.h"

#include "uiModule.h"

#include <SFML/Graphics/RenderWindow.hpp>

#include "uiAppSettings.h"

using RenderWindow = sf::RenderWindow;

class WindowManager : public Module<WindowManager>
{
public:
  virtual void OnStartUp()
  {

  }

  void Clear();

  void Display();

  void Initialize(const AppSettings& gameSettings);


  SharedPtr<RenderWindow> m_mainWindow;
};

