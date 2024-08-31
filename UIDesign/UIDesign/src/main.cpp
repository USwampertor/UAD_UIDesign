#include "imgui.h"
#include "imgui-SFML.h"

#include "uiAnimation.h"
#include "uiAnimator.h"
#include "uiAtlas.h"
#include "uiEntity.h"
#include "uiResourceManager.h"
#include "uiTexture.h"
#include "uiUtilities.h"

#include <cstdlib>
#include <ctime>

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

  // Vector<sf::Texture*> textures;

  // for (int i = 0; i < 6; ++i)
  // {
  //   sf::Texture* t = new sf::Texture();
  //   std::string p = std::filesystem::current_path().string();
  //   String texturePath = Utils::Format("%s/../resources/sprite1.png", FileSystem::CurrentPath().string().c_str());
  //   SharedPtr<Texture> tex = ResourceManager::Instance().LoadResource<Texture>(texturePath);
  //   std::cout << Utils::Format("%s", p.c_str()) << std::endl;
  //   if (t->loadFromFile(Utils::Format("%s/../resources/sprite1.png", FileSystem::CurrentPath().string().c_str()),
  //                        sf::IntRect(i * 128, 0, 128, 128)))
  //   {
  //     t->setSmooth(true);
  //     textures.push_back(t);
  //   }
  // }
  String atlasPath = Utils::Format("%s/../resources/sprite1.json", FileSystem::CurrentPath().string().c_str());
  SharedPtr<Atlas> atlas = ResourceManager::Instance().LoadResource<Atlas>(atlasPath);
  SharedPtr<Animation> animation = ResourceManager::Instance().CreateResource<Animation>("idleEnemy");
  animation->Initialize(atlas->m_atlas, 400.0f);
  // Animation* animation = new Animation();
  // animation->Initialize(textures, 500.0f);
  animation->SetLoop(true);

  // Animator* animator = new Animator();
  // animator->Initialize();
  // animator->AddAnimation(animation, String("idle"));
  // std::cout << Utils::toString(animator->GetSprite()->getPosition().x) << " " <<
  //              Utils::toString(animator->GetSprite()->getPosition().y) << std::endl;
  
  UniquePtr<Entity> e = MakeUniqueObject<Entity>();
  e->Initialize();
  // e->AddComponent(animator);
  e->CreateComponent<Animator>();
  e->GetComponent<Animator>()->Initialize();
  e->GetComponent<Animator>()->AddAnimation(animation, String("idle"));
  e->GetComponent<Animator>()->SetAnimation("idle");
  e->GetComponent<Animator>()->Play();

  SharedPtr<Scene> scene = MakeSharedObject<Scene>();
  scene->Initialize();
  std::srand(std::time(nullptr));
  for (int i = 0; i < 100; ++i)
  {
    scene->m_root->m_children.push_back(MakeUniqueObject<Entity>());
    scene->m_root->m_children[i]->Initialize();
    scene->m_root->m_children[i]->CreateComponent<Animator>();
    scene->m_root->m_children[i]->GetComponent<Animator>()->Initialize();
    scene->m_root->m_children[i]->GetComponent<Animator>()->AddAnimation(animation, String("idle"));
    scene->m_root->m_children[i]->GetComponent<Animator>()->SetAnimation("idle");
    scene->m_root->m_children[i]->GetComponent<Animator>()->SetCurrentTime(std::rand() % 1000);
    scene->m_root->m_children[i]->GetComponent<Animator>()->Play();
    scene->m_root->m_children[i]->Move(Vector2f((std::rand() % 800) - 100, (std::rand() % 800) - 200));
  }

  sf::Clock deltaClock;
  sf::Time dt;
  while (window.isOpen()) {
    sf::Event event;
    float delta = dt.asMilliseconds();
    float fps = 1000.0f / dt.asMilliseconds();
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

    for (int i = 0; i < scene->m_root->m_children.size(); ++i)
    {
      scene->m_root->m_children[i]->Update(delta);
    }
    e->Update(delta);

    ImGui::Begin("Coordinates");
    ImGui::Text(std::to_string(e->GetTransform().position.x).c_str());
    ImGui::Text(std::to_string(e->GetTransform().position.y).c_str());
    ImGui::Text(Utils::ToString(fps).c_str());
    ImGui::End();
    // ImGui::Begin("Test 2");
    // ImGui::End();

    window.clear();
    // Here start drawing
    // window.draw(*(reinterpret_cast<Animator*>(e->GetComponentOfType<Animator*>())->GetSprite()));
    for (int i = 0; i < scene->m_root->m_children.size(); ++i)
    {
      window.draw(scene->m_root->m_children[i]->GetComponent<Animator>()->GetSprite());
    }
    window.draw(e->GetComponent<Animator>()->GetSprite());

    ImGui::SFML::Render(window);
    window.display();
    dt = deltaClock.restart();
  }

  ImGui::SFML::Shutdown();
}