#include "imgui.h"
#include "imgui-SFML.h"

#include "uiAnimation.h"
#include "uiAnimator.h"
#include "uiAtlas.h"
#include "uiBullet.h"
#include "uiBoxCollider.h"
#include "uiEntity.h"
#include "uiInput.h"
#include "uiInputManager.h"
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
  // InputManager::Instance();
  bool debugDraw = false;

  sfp::World w(Vector2f(0, 0));

  String atlasPath = Utils::Format("%s/../resources/sprite1.json", FileSystem::CurrentPath().string().c_str());
  SharedPtr<Atlas> atlas = ResourceManager::Instance().LoadResource<Atlas>(atlasPath);
  SharedPtr<Animation> animation = ResourceManager::Instance().CreateResource<Animation>("idleEnemy");
  animation->Initialize(atlas->m_atlas, 400.0f);
  animation->SetLoop(true);

  SharedPtr<BulletEntity> e = MakeSharedObject<BulletEntity>();

  e->Initialize();
  // e->CreateComponent<Animator>();
  e->GetComponent<Animator>()->Initialize();
  e->GetComponent<Animator>()->AddAnimation(animation, String("idle"));
  e->GetComponent<Animator>()->SetAnimation("idle");
  e->m_map = MakeSharedObject<InputMapping>();
  e->m_map->BindAction(Input::eINPUTCODE::KeyCodeS, std::bind(&BulletEntity::Down, e, std::placeholders::_1));
  e->m_map->BindAction(Input::eINPUTCODE::KeyCodeA, std::bind(&BulletEntity::Left, e, std::placeholders::_1));
  e->m_map->BindAction(Input::eINPUTCODE::KeyCodeD, std::bind(&BulletEntity::Right, e, std::placeholders::_1));
  e->m_map->BindAction(Input::eINPUTCODE::KeyCodeW, std::bind(&BulletEntity::Up, e, std::placeholders::_1));
  InputManager::Instance().RegisterInputMapping(e->m_map);
  e->m_map->m_enabled = true;
  e->GetComponent<BoxCollider>()->setStatic(true);
  e->GetComponent<BoxCollider>()->setSize(Vector2f(e->GetComponent<Animator>()->GetSprite().getTexture()->getSize().x,
                                                   e->GetComponent<Animator>()->GetSprite().getTexture()->getSize().y));
  e->GetComponent<BoxCollider>()->setCenter(e->GetTransform().position);
  w.AddPhysicsBody(*e->GetComponent<BoxCollider>());
  SharedPtr<Scene> scene = MakeSharedObject<Scene>();
  scene->Initialize();
  std::srand(std::time(nullptr));
  for (int i = 0; i < 10; ++i)
  {
    scene->m_root->m_children.push_back(MakeUniqueObject<Entity>());
    scene->m_root->m_children[i]->Initialize();
    scene->m_root->m_children[i]->CreateComponent<Animator>();
    scene->m_root->m_children[i]->GetComponent<Animator>()->Initialize();
    scene->m_root->m_children[i]->GetComponent<Animator>()->AddAnimation(animation, String("idle"));
    scene->m_root->m_children[i]->GetComponent<Animator>()->SetAnimation("idle");
    scene->m_root->m_children[i]->GetComponent<Animator>()->SetCurrentTime(std::rand() % 1000);
    scene->m_root->m_children[i]->GetComponent<Animator>()->Play();
    scene->m_root->m_children[i]->CreateComponent<BoxCollider>();
    scene->m_root->m_children[i]->GetComponent<BoxCollider>()->setStatic(true);
    scene->m_root->m_children[i]->GetComponent<BoxCollider>()->setSize(Vector2f(scene->m_root->m_children[i]->GetComponent<Animator>()->GetSprite().getTexture()->getSize().x,
                                                                                scene->m_root->m_children[i]->GetComponent<Animator>()->GetSprite().getTexture()->getSize().y));
    scene->m_root->m_children[i]->GetComponent<BoxCollider>()->setCenter(scene->m_root->m_children[i]->GetTransform().position);
    w.AddPhysicsBody(*scene->m_root->m_children[i]->GetComponent<BoxCollider>());
    scene->m_root->m_children[i]->Move(Vector2f((std::rand() % 800) - 100, (std::rand() % 800) - 200));
  }

  sf::Clock deltaClock;
  sf::Time dt;
  dt = deltaClock.restart();
  while (window.isOpen()) {
    InputManager::Instance().Update(dt.asMilliseconds());
    sf::Event event;
    float delta = dt.asMilliseconds();
    float fps = 1000.0f / dt.asMilliseconds();
    while (window.pollEvent(event)) {
      ImGui::SFML::ProcessEvent(window, event);
      InputManager::Instance().PollEvents(event);
      if (event.type == sf::Event::Closed) { window.close(); }
    }

    ImGui::SFML::Update(window, dt);

    for (int i = 0; i < scene->m_root->m_children.size(); ++i)
    {
      scene->m_root->m_children[i]->Update(delta);
    }
    e->Update(delta);

    if (InputManager::Instance().m_values[Input::eINPUTCODE::KeyCodeL][0]->GetState() == Input::eINPUTSTATE::PRESSED)
    {
      debugDraw = !debugDraw;
    }

    ImGui::Begin("Coordinates");
    ImGui::Text(std::to_string(e->m_direction.x).c_str());
    ImGui::Text(std::to_string(e->m_direction.y).c_str());
    ImGui::Text(InputManager::Instance().m_values[Input::eINPUTCODE::KeyCodeW][0]->GetState()._to_string());
    ImGui::Text(InputManager::Instance().m_values[Input::eINPUTCODE::KeyCodeA][0]->GetState()._to_string());
    ImGui::Text(InputManager::Instance().m_values[Input::eINPUTCODE::KeyCodeS][0]->GetState()._to_string());
    ImGui::Text(InputManager::Instance().m_values[Input::eINPUTCODE::KeyCodeD][0]->GetState()._to_string());
    ImGui::Text(Utils::ToString(fps).c_str());
    ImGui::End();
    w.UpdatePhysics(10);

    window.clear();
    // Here start drawing
    for (int i = 0; i < scene->m_root->m_children.size(); ++i)
    {
      if (debugDraw)
      {
        window.draw(*scene->m_root->m_children[i]->GetComponent<BoxCollider>());
      }

      window.draw(scene->m_root->m_children[i]->GetComponent<Animator>()->GetSprite());
    }
    if (debugDraw)
    {
      window.draw(*e->GetComponent<BoxCollider>());
    }
    window.draw(e->GetComponent<Animator>()->GetSprite());

    ImGui::SFML::Render(window);
    window.display();
    dt = deltaClock.restart();
  }

  ImGui::SFML::Shutdown();
}