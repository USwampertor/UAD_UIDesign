#include "imgui.h"
#include "imgui-SFML.h"

#include "uiAnimation.h"

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>

int main() {
  sf::RenderWindow window(sf::VideoMode(640, 480), "");
  window.setFramerateLimit(60);
  ImGui::SFML::Init(window);

  Vector<sf::Texture*> textures;

  for (int i = 0; i < 6; ++i)
  {
    sf::Texture* t = new sf::Texture();
    if (t->loadFromFile("D:/University/UAD_UIDesign/UIDesign/resources/sprite1.png",
                         sf::IntRect(i * 128, 0, 128, 128)))
    {
      t->setSmooth(true);
      textures.push_back(t);
    }
  }

  Animation* animation = new Animation();

  animation->Initialize(textures, 500.0f);
  animation->SetLoop(true);


  sf::Clock deltaClock;
  while (window.isOpen()) {
    sf::Time dt = deltaClock.restart();
    sf::Event event;
    while (window.pollEvent(event)) {
      ImGui::SFML::ProcessEvent(window, event);

      if (event.type == sf::Event::Closed) {
        window.close();
      }
    }

    ImGui::SFML::Update(window, dt);
    animation->Update(dt.asMilliseconds());

    ImGui::Begin("Hello, world!");
    ImGui::Button("Look at this pretty button");
    ImGui::Text(std::to_string(dt.asMilliseconds()).c_str());
    ImGui::End();
    ImGui::Begin("Test 2");
    ImGui::End();

    window.clear();
    ImGui::SFML::Render(window);
    window.display();
  }

  ImGui::SFML::Shutdown();
}