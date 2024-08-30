#include "imgui.h"
#include "imgui-SFML.h"

#include "uiAnimation.h"
#include "uiAnimator.h"
#include "uiEntity.h"
#include "uiResourceManager.h"
#include "uiTexture.h"
#include "uiUtilities.h"

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>

#include <iostream>

int main() {
  ResourceManager::StartUp();
  sf::RenderWindow window(sf::VideoMode(640, 480), "");
  window.setFramerateLimit(60);
  ImGui::SFML::Init(window);

  Vector<sf::Texture*> textures;

  for (int i = 0; i < 6; ++i)
  {
    sf::Texture* t = new sf::Texture();
    std::string p = std::filesystem::current_path().string();
    String texturePath = Utils::Format("%s/../resources/sprite1.png", FileSystem::CurrentPath().string().c_str());
    SharedPtr<Texture> tex = ResourceManager()::Instance().LoadResource(texturePath);
    std::cout << Utils::Format("%s", p.c_str()) << std::endl;
    if (t->loadFromFile(Utils::Format("%s/../resources/sprite1.png", FileSystem::CurrentPath().string().c_str()),
                         sf::IntRect(i * 128, 0, 128, 128)))
    {
      t->setSmooth(true);
      textures.push_back(t);
    }
  }

  // Animation* animation = new Animation();
  // animation->Initialize(textures, 500.0f);
  // animation->SetLoop(true);

  // Animator* animator = new Animator();
  // animator->Initialize();
  // animator->AddAnimation(animation, String("idle"));
  // std::cout << Utils::toString(animator->GetSprite()->getPosition().x) << " " <<
  //              Utils::toString(animator->GetSprite()->getPosition().y) << std::endl;
  
  Entity* e = new Entity();
  e->Initialize();
  // e->AddComponent(animator);
  auto animator = e->CreateComponent<Animator>();
  animator->Initialize();
  // animator->AddAnimation(animation, String("idle"));
  e->GetComponent<Animator>()->SetAnimation("idle");
  e->GetComponent<Animator>()->Play();

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

    ImGui::Begin("Coordinates");
    ImGui::Text(std::to_string(e->GetTransform().position.x).c_str());
    ImGui::Text(std::to_string(e->GetTransform().position.y).c_str());
    ImGui::End();
    // ImGui::Begin("Test 2");
    // ImGui::End();

    window.clear();
    // Here start drawing
    // window.draw(*(reinterpret_cast<Animator*>(e->GetComponentOfType<Animator*>())->GetSprite()));
    window.draw(e->GetComponent<Animator>()->GetSprite());

    ImGui::SFML::Render(window);
    window.display();
  }

  ImGui::SFML::Shutdown();
}