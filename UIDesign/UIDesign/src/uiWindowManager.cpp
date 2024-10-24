#include "uiWindowManager.h"
#include "uiApp.h"

void WindowManager::Initialize(const AppSettings& gameSettings)
{
  // m_mainWindow = MakeSharedObject<RenderWindow>(gameSettings.m_displaySize, gameSettings.m_gameName);
  m_mainWindow.create(gameSettings.m_displaySize, gameSettings.m_gameName);
  m_mainWindow.setVerticalSyncEnabled(gameSettings.m_shouldUseVerticalSync);
  m_mainWindow.setFramerateLimit(gameSettings.m_framerate);
  m_mainWindow.setActive(true);
}

void WindowManager::Clear()
{
#if UI_EDITOR_MODE
  m_mainWindow.clear(App::Instance().m_editor->m_editorColor);
#else
  m_mainWindow.clear();
#endif
}

void WindowManager::Display()
{
  m_mainWindow.display();
}