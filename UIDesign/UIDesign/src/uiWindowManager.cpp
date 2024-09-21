#include "uiWindowManager.h"


void WindowManager::Initialize(const GameSettings& gameSettings)
{
  m_mainWindow = MakeSharedObject<RenderWindow>(gameSettings.m_displaySize, gameSettings.m_gameName);
  m_mainWindow->setVerticalSyncEnabled(gameSettings.m_shouldUseVerticalSync);
  m_mainWindow->setFramerateLimit(gameSettings.m_framerate);
}

void WindowManager::Clear()
{
  m_mainWindow->clear();
}

void WindowManager::Display()
{
  m_mainWindow->display();
}