#include "uiApp.h"

#include "uiAudioSource.h"
#include "uiAudioListener.h"
#include "uiBullet.h"
#include "uiCameraFollower.h"
#include "uiEnemy.h"
#include "uiInputManager.h"
#include "uiPhysics.h"
#include "uiPlayer.h"
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
  ResourceManager::Instance().GetResource<Animation>("idleEnemy")->Initialize(ResourceManager::Instance().GetResource<Atlas>("sprite1")->m_atlas, 400.0f);
  ResourceManager::Instance().GetResource<Animation>("idleEnemy")->SetLoop(true);
  String atlasPath2 = Utils::Format("%s/../resources/sprite2.json", FileSystem::CurrentPath().string().c_str());
  ResourceManager::Instance().LoadResource<Atlas>(atlasPath2);
  ResourceManager::Instance().CreateResource<Animation>("idleBullet");
  ResourceManager::Instance().GetResource<Animation>("idleBullet")->Initialize(ResourceManager::Instance().GetResource<Atlas>("sprite2")->m_atlas, 400.0f);
  ResourceManager::Instance().GetResource<Animation>("idleBullet")->SetLoop(true);
  String playerPath = Utils::Format("%s/../resources/player.json", FileSystem::CurrentPath().string().c_str());
  ResourceManager::Instance().LoadResource<Atlas>(playerPath);
  ResourceManager::Instance().CreateResource<Animation>("idlePlayer");
  ResourceManager::Instance().GetResource<Animation>("idlePlayer")->Initialize(ResourceManager::Instance().GetResource<Atlas>("player")->m_atlas, 800.0f);
  ResourceManager::Instance().GetResource<Animation>("idlePlayer")->SetLoop(true);
  String playerWalkingPath = Utils::Format("%s/../resources/playerwalking.json", FileSystem::CurrentPath().string().c_str());
  ResourceManager::Instance().LoadResource<Atlas>(playerWalkingPath);
  ResourceManager::Instance().CreateResource<Animation>("walkingPlayer");
  ResourceManager::Instance().GetResource<Animation>("walkingPlayer")->Initialize(ResourceManager::Instance().GetResource<Atlas>("playerwalking")->m_atlas, 400.0f);
  ResourceManager::Instance().GetResource<Animation>("walkingPlayer")->SetLoop(true);

  String audioPath = Utils::Format("%s/../resources/pingas.mp3", FileSystem::CurrentPath().string().c_str());
  ResourceManager::Instance().LoadResource<AudioClip>(audioPath);
  String audioPath2 = Utils::Format("%s/../resources/ping.mp3", FileSystem::CurrentPath().string().c_str());
  ResourceManager::Instance().LoadResource<AudioClip>(audioPath2);



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

  PlayerEntity* e = SceneManager::Instance().CreateObject<PlayerEntity>("Player");
  e->GetComponent<AudioSource>()->SetClip(ResourceManager::Instance().GetResource<AudioClip>("pingas"));
  // e->GetComponent<Animator>()->Initialize();
  e->GetComponent<Animator>()->AddAnimation(ResourceManager::Instance().GetResource<Animation>("idlePlayer"), "idle");
  e->GetComponent<Animator>()->AddAnimation(ResourceManager::Instance().GetResource<Animation>("walkingPlayer"), "walking");
  e->GetComponent<Animator>()->SetAnimation("idle");
  e->GetComponent<Animator>()->Play();

  e->m_map = MakeSharedObject<InputMapping>();
  e->m_map->BindAction(Input::eINPUTCODE::KeyCodeW, std::bind(&PlayerEntity::Up, e, std::placeholders::_1));
  e->m_map->BindAction(Input::eINPUTCODE::KeyCodeA, std::bind(&PlayerEntity::Left, e, std::placeholders::_1));
  e->m_map->BindAction(Input::eINPUTCODE::KeyCodeS, std::bind(&PlayerEntity::Down, e, std::placeholders::_1));
  e->m_map->BindAction(Input::eINPUTCODE::KeyCodeD, std::bind(&PlayerEntity::Right, e, std::placeholders::_1));
  e->m_map->BindAction(Input::eINPUTCODE::KeyCodeEnter, std::bind(&PlayerEntity::PlaySound, e, std::placeholders::_1));
  InputManager::Instance().RegisterInputMapping(e->m_map);
  e->m_map->m_enabled = true;
  e->GetComponent<BoxCollider>()->setStatic(true);
  e->GetComponent<BoxCollider>()->setSize(Vector2f(e->GetComponent<Animator>()->GetSprite().getTexture()->getSize().x,
                                                   e->GetComponent<Animator>()->GetSprite().getTexture()->getSize().y));
  e->GetComponent<BoxCollider>()->setCenter(e->GetTransform().position);

  e->CreateComponent<AudioListener>();
  // e->CreateComponent<AudioListener>()->SetVolume(100);

  SceneManager::Instance().CreateObject<CameraFollower>();

  std::srand(std::time(nullptr));
  for (int i = 0; i < 10; ++i)
  {
    EnemyEntity* newE = SceneManager::Instance().CreateObject<EnemyEntity>(Utils::Format("Enemy_%d", i));
    // scene->m_root->m_children.push_back(MakeUniqueObject<Entity>());
    // newE->Initialize();
    newE->CreateComponent<Animator>();
    // newE->GetComponent<Animator>()->Initialize();
    newE->GetComponent<Animator>()->AddAnimation(ResourceManager::Instance().GetResource<Animation>("idleEnemy"), String("idle"));
    newE->GetComponent<Animator>()->SetAnimation("idle");
    newE->GetComponent<Animator>()->SetCurrentTime(std::rand() % 1000);
    newE->GetComponent<Animator>()->Play();
    newE->CreateComponent<BoxCollider>();
    newE->GetComponent<BoxCollider>()->setStatic(false);
    newE->GetComponent<BoxCollider>()->setMass(5);
    newE->GetComponent<BoxCollider>()->setLayer(ePHYSICLAYERS::DEFAULT, 1);
    newE->GetComponent<BoxCollider>()->setSize(Vector2f(newE->GetComponent<Animator>()->GetSprite().getTexture()->getSize().x,
      newE->GetComponent<Animator>()->GetSprite().getTexture()->getSize().y));
    newE->GetComponent<BoxCollider>()->setCenter(newE->GetTransform().position);
    // Physics::Instance().RegisterPhysicsBody(*newE->GetComponent<BoxCollider>());
    // w.AddPhysicsBody(*newE->GetComponent<BoxCollider>());
    newE->CreateComponent<AudioSource>();
    newE->GetComponent<AudioSource>()->SetClip(ResourceManager::Instance().GetResource<AudioClip>("ping"));
    newE->GetComponent<AudioSource>()->SetMinDistance(150);
    newE->GetComponent<AudioSource>()->SetAttenuation(5);
    newE->GetComponent<AudioSource>()->SetLoop(false);

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

    ImGui::Begin("Coordinates");
    ImGui::Text(Utils::Format("%f , %f", e->GetTransform().position.x, e->GetTransform().position.y).c_str());
    ImGui::Text(Utils::Format("%f , %f", Listener::getPosition().x, Listener::getPosition().y).c_str());

    ImGui::End();

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