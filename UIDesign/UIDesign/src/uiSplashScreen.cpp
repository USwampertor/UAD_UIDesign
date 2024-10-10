#include "uiSplashScreen.h"

#include "uiFileSystem.h"
#include "uiUtilities.h"

#include <SFML/Graphics.hpp>

void SplashScreen::Initialize()
{
  m_loaded = false;
  m_splashTexture.loadFromFile(Utils::Format("%s/../resources/splash.png", 
                               FileSystem::CurrentPath().string().c_str()));
  m_splashSprite.setTexture(m_splashTexture);
  m_defaultFont.loadFromFile(Utils::Format("%s/../resources/DePixelKlein.ttf",
                             FileSystem::CurrentPath().string().c_str()));
  m_splashText.setPosition(10, 550);
  m_splashText.setFont(m_defaultFont);
  m_splashText.setString("Loading");
}

void SplashScreen::Show()
{
  m_hwnd.create(VideoMode(800, 600), "UI", eWINDOWSTYLE::NONE);
  while (m_hwnd.isOpen())
  {
    sf::Event event;
    while (m_hwnd.pollEvent(event))
    {
      if (event.type == sf::Event::Closed)
        m_hwnd.close();
    }

    if (m_loaded)
    {
      ShutDown();
    }
    else
    {
      m_hwnd.clear();
      m_hwnd.draw(m_splashSprite);
      m_hwnd.draw(m_splashText);
      m_hwnd.display();
    }
  }
}

void SplashScreen::ShutDown()
{
  m_hwnd.close();
}

