#include "imgui.h"
#include "imgui-SFML.h"

#include "uiAnimation.h"
#include "uiAnimator.h"
#include "uiAtlas.h"
#include "uiBullet.h"
#include "uiEntity.h"
#include "uiInput.h"
#include "uiInputMapping.h"
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
  sf::RenderWindow window(sf::VideoMode(640, 480), "");
  window.setFramerateLimit(144);
  ImGui::SFML::Init(window);
  ResourceManager::StartUp();
  InputManager::StartUp();
  InputManager::Instance().SetDisplaySize(640, 480);



  String atlasPath = Utils::Format("%s/../resources/sprite1.json", FileSystem::CurrentPath().string().c_str());
  SharedPtr<Atlas> atlas = ResourceManager::Instance().LoadResource<Atlas>(atlasPath);
  SharedPtr<Animation> animation = ResourceManager::Instance().CreateResource<Animation>("idleEnemy");
  animation->Initialize(atlas->m_atlas, 400.0f);
  animation->SetLoop(true);

  UniquePtr<BulletEntity> e = MakeUniqueObject<BulletEntity>();

  e->Initialize();
  e->CreateComponent<Animator>();
  e->GetComponent<Animator>()->Initialize();
  e->GetComponent<Animator>()->AddAnimation(animation, String("idle"));
  e->GetComponent<Animator>()->SetAnimation("idle");
  e->GetComponent<Animator>()->Play();
  e->m_map = MakeSharedObject<InputMapping>(InputManager::Instance());
  SharedPtr<Scene> scene = MakeSharedObject<Scene>();
  scene->Initialize();
  std::srand(std::time(nullptr));
  for (int i = 0; i < 10000; ++i)
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
    InputManager::Instance().Update();

    {
      
    }

    sf::Event event;
    float delta = dt.asMilliseconds();
    float fps = 1000.0f / dt.asMilliseconds();
    while (window.pollEvent(event)) {
      ImGui::SFML::ProcessEvent(window, event);
      if (event.type == sf::Event::Closed) { window.close(); }
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

    window.clear();
    // Here start drawing
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