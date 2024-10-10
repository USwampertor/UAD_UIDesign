#pragma once

#include "uiPrerequisites.h"

#include "uiAppSettings.h"
#include "uiModule.h"
#include "uiUtilities.h"
#include "uiWindow.h"

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

