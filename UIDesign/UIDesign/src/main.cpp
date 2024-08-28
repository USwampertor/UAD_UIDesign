#include "imgui.h"
#include "imgui-SFML.h"

#include "uiAnimation.h"
#include "uiAnimator.h"
#include "uiEntity.h"

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>

#include <iostream>

int main() {
  sf::RenderWindow window(sf::VideoMode(640, 480), "");
  window.setFramerateLimit(60);
  ImGui::SFML::Init(window);

  Vector<sf::Texture*> textures;

  for (int i = 0; i < 6; ++i)
  {
    sf::Texture* t = new sf::Texture();
    std::string p = std::filesystem::current_path().string();
    std::cout << Utils::format("%s", p.c_str()) << std::endl;
    if (t->loadFromFile(Utils::format("%s/../resources/sprite1.png", FileSystem::CurrentPath().string().c_str()),
                         sf::IntRect(i * 128, 0, 128, 128)))
    {
      t->setSmooth(true);
      textures.push_back(t);
    }
  }

  Animation* animation = new Animation();
  animation->Initialize(textures, 500.0f);
  animation->SetLoop(true);

  Animator* animator = new Animator();
  animator->Initialize();
  animator->AddAnimation(animation, String("idle"));
  std::cout << Utils::toString(animator->GetSprite()->getPosition().x) << " " <<
               Utils::toString(animator->GetSprite()->getPosition().y) << std::endl;
  
  Entity* e = new Entity();
  e->Initialize();
  e->AddComponent(animator);
  reinterpret_cast<Animator*>(e->GetComponent("Animator"))->SetAnimation("idle");
  reinterpret_cast<Animator*>(e->GetComponent("Animator"))->Play();

  std::cout << Utils::toString(e->m_transform.position.x) << " " <<
               Utils::toString(e->m_transform.position.y) << std::endl;

  std::cout << Utils::toString(animator->GetSprite()->getPosition().x) << " " <<
               Utils::toString(animator->GetSprite()->getPosition().y) << std::endl;

  sf::Clock deltaClock;
  while (window.isOpen()) {
    sf::Time dt = deltaClock.restart();
    sf::Event event;
    while (window.pollEvent(event)) {
      ImGui::SFML::ProcessEvent(window, event);

      if (event.type == sf::Event::Closed) {
        window.close();
      }
      if (event.type == sf::Event::KeyPressed)
      {
        if (event.key.scancode == sf::Keyboard::Scan::W)
        {
          e->Move(sf::Vector2f(0.0f, -10.0f));
        }
        if (event.key.scancode == sf::Keyboard::Scan::S)
        {
          e->Move(sf::Vector2f(0.0f, 10.0f));
        }
        if (event.key.scancode == sf::Keyboard::Scan::A)
        {
          e->Move(sf::Vector2f(-10.0f, 0.0f));
        }
        if (event.key.scancode == sf::Keyboard::Scan::D)
        {
          e->Move(sf::Vector2f(10.0f, 0.0f));
        }
      }
    }

    ImGui::SFML::Update(window, dt);
    e->Update(dt.asMilliseconds());

    ImGui::Begin("Hello, world!");
    ImGui::Button("Look at this pretty button");
    ImGui::Text(std::to_string(e->m_transform.position.x).c_str());
    ImGui::Text(std::to_string(e->m_transform.position.y).c_str());
    ImGui::End();
    ImGui::Begin("Test 2");
    ImGui::End();

    window.clear();
    //Here start drawing
    window.draw(*(reinterpret_cast<Animator*>(e->GetComponent("Animator"))->GetSprite()));


    ImGui::SFML::Render(window);
    window.display();
  }

  ImGui::SFML::Shutdown();
}