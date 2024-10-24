#pragma once

#include "uiPrerequisites.h"
#include "uiSprite.h"
#include "uiTexture.h"
#include "uiWindow.h"
#include "uiFont.h"
#include "uiText.h"

// Forward declaration
struct Log;

class SplashScreen
{
public:
  void Initialize();

  void Show();

  void ShutDown();

  bool m_loaded;

  void SetLog(const Log& newLog);

  void SetTaskString(const String& newTaskString) 
  { 
    m_activeTask = newTaskString; 
    m_splashText.setString(m_activeTask);
  }

private:

  RenderWindow m_hwnd;

  Texture m_splashTexture;
  Sprite m_splashSprite;
  String m_activeTask;
  Font m_defaultFont;
  Text m_splashText;
};

