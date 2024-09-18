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
#include "uiPhysics.h"
#include "uiResourceManager.h"
#include "uiSceneManager.h"
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
  SceneManager::StartUp();
  // InputManager::Instance();
  Physics::StartUp();
  Physics::Instance().SetGravity(Vector2f(0, 0));
  // sfp::World w(Vector2f(0, 0));

  String atlasPath1 = Utils::Format("%s/../resources/sprite1.json", FileSystem::CurrentPath().string().c_str());
  SharedPtr<Atlas> atlas1 = ResourceManager::Instance().LoadResource<Atlas>(atlasPath1);
  SharedPtr<Animation> animation1 = ResourceManager::Instance().CreateResource<Animation>("idleEnemy");
  String atlasPath2 = Utils::Format("%s/../resources/sprite2.json", FileSystem::CurrentPath().string().c_str());
  SharedPtr<Atlas> atlas2 = ResourceManager::Instance().LoadResource<Atlas>(atlasPath2);
  SharedPtr<Animation> animation2 = ResourceManager::Instance().CreateResource<Animation>("idleBullet");
  animation1->Initialize(atlas1->m_atlas, 400.0f);
  animation2->Initialize(atlas2->m_atlas, 400.0f);
  animation1->SetLoop(true);
  animation2->SetLoop(true);

  SceneManager::Instance().CreateScene("TestScene");
  SceneManager::Instance().ChangeScene("TestScene");

  // SharedPtr<BulletEntity> e = MakeSharedObject<BulletEntity>();

  BulletEntity* e = SceneManager::Instance().CreateObject<BulletEntity>();

  // e->Initialize();
  // e->CreateComponent<Animator>();
  e->GetComponent<Animator>()->Initialize();
  e->GetComponent<Animator>()->AddAnimation(animation2, String("idle"));
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
  Physics::Instance().RegisterPhysicsBody(*e->GetComponent<BoxCollider>());
  // w.AddPhysicsBody(*e->GetComponent<BoxCollider>());
  // SharedPtr<Scene> scene = MakeSharedObject<Scene>();
  // scene->Initialize();
  std::srand(std::time(nullptr));
  for (int i = 0; i < 10; ++i)
  {
    Entity* newE = SceneManager::Instance().CreateObject<Entity>();
    // scene->m_root->m_children.push_back(MakeUniqueObject<Entity>());
    // newE->Initialize();
    newE->CreateComponent<Animator>();
    newE->GetComponent<Animator>()->Initialize();
    newE->GetComponent<Animator>()->AddAnimation(animation1, String("idle"));
    newE->GetComponent<Animator>()->SetAnimation("idle");
    newE->GetComponent<Animator>()->SetCurrentTime(std::rand() % 1000);
    newE->GetComponent<Animator>()->Play();
    newE->CreateComponent<BoxCollider>();
    newE->GetComponent<BoxCollider>()->setStatic(true);
    newE->GetComponent<BoxCollider>()->setSize(Vector2f(newE->GetComponent<Animator>()->GetSprite().getTexture()->getSize().x,
                                                        newE->GetComponent<Animator>()->GetSprite().getTexture()->getSize().y));
    newE->GetComponent<BoxCollider>()->setCenter(newE->GetTransform().position);
    Physics::Instance().RegisterPhysicsBody(*newE->GetComponent<BoxCollider>());
    // w.AddPhysicsBody(*newE->GetComponent<BoxCollider>());
    newE->Move(Vector2f((std::rand() % 800) - 100, (std::rand() % 800) - 200));
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

    SceneManager::Instance().Update(delta);
    // for (int i = 0; i < scene->m_root->m_children.size(); ++i)
    // {
    // }
    // e->Update(delta);

    if (InputManager::Instance().m_values[Input::eINPUTCODE::KeyCodeL][0]->GetState() == Input::eINPUTSTATE::PRESSED)
    {
      SceneManager::Instance().m_isDebug = !SceneManager::Instance().m_isDebug;
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
    // w.UpdatePhysics(10);
    Physics::Instance().Update(10);
    window.clear();

    SceneManager::Instance().UpdateRender(window);
    // Here start drawing
    // for (int i = 0; i < SceneManager::Instance().GetActiveScene()->m_entities.size(); ++i)
    // {
    //   if (debugDraw)
    //   {
    //     window.draw(*SceneManager::Instance().GetActiveScene()->m_entities[i]->GetComponent<BoxCollider>());
    //   }
    // 
    //   window.draw(SceneManager::Instance().GetActiveScene()->m_entities[i]->GetComponent<Animator>()->GetSprite());
    // }
    // if (debugDraw)
    // {
    //   window.draw(*e->GetComponent<BoxCollider>());
    // }
    // window.draw(e->GetComponent<Animator>()->GetSprite());

    ImGui::SFML::Render(window);
    window.display();
    dt = deltaClock.restart();
  }

  ImGui::SFML::Shutdown();
}