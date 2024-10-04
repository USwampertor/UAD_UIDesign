#pragma once

#include "uiPrerequisites.h"

#include "uiModule.h"

#include "imgui.h"
#include "imgui-SFML.h"


// TODO: Change all this
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>

using RenderWindow = sf::RenderWindow;
using HEvent = sf::Event;
using Time = sf::Time;
using Clock = sf::Clock;

class UI : public Module<UI>
{
public:
  virtual void OnStartUp() override
  {

  }

  void Initialize(RenderWindow& window);

  void ProcessEvent(const RenderWindow& window, const HEvent& event);

  void Update( RenderWindow& window,  Time& dt);

  void RenderUI();

  void Render(RenderWindow& window);

  void Finish();

};

