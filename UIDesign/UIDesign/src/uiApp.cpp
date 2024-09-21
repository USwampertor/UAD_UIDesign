#include "uiApp.h"

#include "uiAudioSource.h"
#include "uiBullet.h"
#include "uiInputManager.h"
#include "uiPhysics.h"
#include "uiResourceManager.h"
#include "uiSceneManager.h"
#include "uiUI.h"
#include "uiTexture.h"
#include "uiWindowManager.h"


void App::OnStartUp()
{
  if (!StartSystems())
  {
    // Send systems error
  }
  if (!LoadResources())
  {
    // Send Resources error
  }
}

bool App::StartSystems()
{
  ResourceManager::StartUp();
  if (!ResourceManager::IsStarted())
  {
    // Error loading Resource Manager
  }
  InputManager::StartUp();
  if (!InputManager::IsStarted())
  {
    // Error loading Input Manager
  }
  SceneManager::StartUp();
  if (!SceneManager::IsStarted())
  {
    // Error loading Scene Manager
  }
  Physics::StartUp();
  if (!Physics::IsStarted())
  {
    // Error loading Physics
  }
  WindowManager::StartUp();
  if (!WindowManager::IsStarted())
  {
    // Error loading Window Manager
  }
  UI::StartUp();
  if (!UI::IsStarted())
  {
    // Error loading UI
  }
  return true;
}

bool App::LoadResources()
{
  String atlasPath1 = Utils::Format("%s/../resources/sprite1.json", FileSystem::CurrentPath().string().c_str());
  ResourceManager::Instance().LoadResource<Atlas>(atlasPath1);
  ResourceManager::Instance().CreateResource<Animation>("idleEnemy");
  String atlasPath2 = Utils::Format("%s/../resources/sprite2.json", FileSystem::CurrentPath().string().c_str());
  ResourceManager::Instance().LoadResource<Atlas>(atlasPath2);
  ResourceManager::Instance().CreateResource<Animation>("idleBullet");
  ResourceManager::Instance().GetResource<Animation>("idleBullet")->Initialize(ResourceManager::Instance().GetResource<Atlas>("sprite1")->m_atlas, 400.0f);
  ResourceManager::Instance().GetResource<Animation>("idleBullet")->SetLoop(true);
  ResourceManager::Instance().GetResource<Animation>("idleEnemy")->Initialize(ResourceManager::Instance().GetResource<Atlas>("sprite2")->m_atlas, 400.0f);
  ResourceManager::Instance().GetResource<Animation>("idleEnemy")->SetLoop(true);
  String audioPath = Utils::Format("%s/../resources/pingas.mp3", FileSystem::CurrentPath().string().c_str());
  ResourceManager::Instance().LoadResource<AudioClip>(audioPath);


  String settingsPath = Utils::Format("%s/../resources/game.settings", FileSystem::CurrentPath().string().c_str());
  GameSettings settings;
  settings.FromFile(settingsPath);
  WindowManager::Instance().Initialize(settings);
  UI::Instance().Initialize(*WindowManager::Instance().m_mainWindow.get());


  SceneManager::Instance().CreateScene("TestScene");
  SceneManager::Instance().ChangeScene("TestScene");

  return true;
}

void App::Run()
{
  
  Update();
  Exit();
}

void App::Update()
{

  BulletEntity* e = SceneManager::Instance().CreateObject<BulletEntity>();
  e->GetComponent<AudioSource>()->SetClip(ResourceManager::Instance().GetResource<AudioClip>("pingas"));
  // e->GetComponent<Animator>()->Initialize();
  e->GetComponent<Animator>()->AddAnimation(ResourceManager::Instance().GetResource<Animation>("idleEnemy"), "idle");
  e->GetComponent<Animator>()->SetAnimation("idle");

  e->m_map = MakeSharedObject<InputMapping>();
  e->m_map->BindAction(Input::eINPUTCODE::KeyCodeW, std::bind(&BulletEntity::Up, e, std::placeholders::_1));
  e->m_map->BindAction(Input::eINPUTCODE::KeyCodeA, std::bind(&BulletEntity::Left, e, std::placeholders::_1));
  e->m_map->BindAction(Input::eINPUTCODE::KeyCodeS, std::bind(&BulletEntity::Down, e, std::placeholders::_1));
  e->m_map->BindAction(Input::eINPUTCODE::KeyCodeD, std::bind(&BulletEntity::Right, e, std::placeholders::_1));
  e->m_map->BindAction(Input::eINPUTCODE::KeyCodeEnter, std::bind(&BulletEntity::PlaySound, e, std::placeholders::_1));
  InputManager::Instance().RegisterInputMapping(e->m_map);
  e->m_map->m_enabled = true;
  e->GetComponent<BoxCollider>()->setStatic(true);
  e->GetComponent<BoxCollider>()->setSize(Vector2f(e->GetComponent<Animator>()->GetSprite().getTexture()->getSize().x,
                                                   e->GetComponent<Animator>()->GetSprite().getTexture()->getSize().y));
  e->GetComponent<BoxCollider>()->setCenter(e->GetTransform().position);


  std::srand(std::time(nullptr));
  for (int i = 0; i < 10; ++i)
  {
    Entity* newE = SceneManager::Instance().CreateObject<Entity>();
    // scene->m_root->m_children.push_back(MakeUniqueObject<Entity>());
    // newE->Initialize();
    newE->CreateComponent<Animator>();
    // newE->GetComponent<Animator>()->Initialize();
    newE->GetComponent<Animator>()->AddAnimation(ResourceManager::Instance().GetResource<Animation>("idleBullet"), String("idle"));
    newE->GetComponent<Animator>()->SetAnimation("idle");
    newE->GetComponent<Animator>()->SetCurrentTime(std::rand() % 1000);
    newE->GetComponent<Animator>()->Play();
    newE->CreateComponent<BoxCollider>();
    newE->GetComponent<BoxCollider>()->setStatic(std::rand() % 2 == 0 ? true : false);
    newE->GetComponent<BoxCollider>()->setMass(std::rand() % 2 == 0 ? std::rand() % 10 : 1);
    newE->GetComponent<BoxCollider>()->setSize(Vector2f(newE->GetComponent<Animator>()->GetSprite().getTexture()->getSize().x,
      newE->GetComponent<Animator>()->GetSprite().getTexture()->getSize().y));
    newE->GetComponent<BoxCollider>()->setCenter(newE->GetTransform().position);
    // Physics::Instance().RegisterPhysicsBody(*newE->GetComponent<BoxCollider>());
    // w.AddPhysicsBody(*newE->GetComponent<BoxCollider>());
    newE->Move(Vector2f((std::rand() % 800) - 100, (std::rand() % 800) - 200));
  }

  Clock deltaClock;
  Time dt;

  dt = deltaClock.restart();

  while (WindowManager::Instance().m_mainWindow->isOpen()) {
    InputManager::Instance().Update(dt.asMilliseconds());
    HEvent event;
    float delta = dt.asMilliseconds();
    float fps = 1000.0f / dt.asMilliseconds();
    while (WindowManager::Instance().m_mainWindow->pollEvent(event)) {
      ImGui::SFML::ProcessEvent(*WindowManager::Instance().m_mainWindow.get(), event);
      InputManager::Instance().PollEvents(event);
      if (event.type == HEvent::Closed) { WindowManager::Instance().m_mainWindow->close(); }
    }
    UI::Instance().Update(*WindowManager::Instance().m_mainWindow.get(), dt);

    if (InputManager::Instance().m_values[Input::eINPUTCODE::KeyCodeL][0]->GetState() == Input::eINPUTSTATE::PRESSED)
    {
      SceneManager::Instance().m_isDebug = !SceneManager::Instance().m_isDebug;
    }

    UI::Instance().RenderUI();

    Physics::Instance().Update(10);
    SceneManager::Instance().Update(delta);

    WindowManager::Instance().Clear();

    SceneManager::Instance().UpdateRender(*WindowManager::Instance().m_mainWindow.get());

    UI::Instance().Render(*WindowManager::Instance().m_mainWindow.get());
    WindowManager::Instance().Display();

    dt = deltaClock.restart();
  }
}

void App::Exit()
{
  UI::Instance().Finish();
}