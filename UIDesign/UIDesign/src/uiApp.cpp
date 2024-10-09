#include "uiApp.h"

#include "uiAudioSource.h"
#include "uiAudioListener.h"
#include "uiBullet.h"
#include "uiCameraFollower.h"
#include "uiEnemy.h"
#include "uiFileSystem.h"
#include "uiInputManager.h"
#include "uiPhysics.h"
#include "uiPlayer.h"
#include "uiResourceManager.h"
#include "uiSceneManager.h"
#include "uiUI.h"
#include "uiTexture.h"
#include "uiWindowManager.h"

#include "Remotery.h"


void App::OnStartUp()
{
  if (!StartSystems())
  {
    // Send systems error
    exit(403);
  }
  if (!LoadResources())
  {
    // Send Resources error
  }
}

bool App::StartSystems()
{
  Remotery* rmt;
  rmtError error = rmt_CreateGlobalInstance(&rmt);
  
  if (RMT_ERROR_NONE != error)
  {
    std::cout << "Error starting up Remotery" << std::endl;
    return false;
  }

  rmt_BindOpenGL();

  rmt_ScopedCPUSample(StartSystems, 0);

  ResourceManager::StartUp();
  if (!ResourceManager::IsStarted())
  {
    // Error loading Resource Manager
    std::cout << "Error starting up resource manager" << std::endl;
    return false;
  }
  else
  {
    std::cout << "Resource Manager working correctly" << std::endl;
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
  ResourceManager::Instance().LoadResource<Texture>(Utils::Format("%s/../resources/gizmo.png", FileSystem::CurrentPath().string().c_str()));
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
  ResourceManager::Instance().LoadResource<AudioClip>(Utils::Format("%s/../resources/fart.mp3", FileSystem::CurrentPath().string().c_str()));


  String settingsPath = Utils::Format("%s/../resources/game.settings", FileSystem::CurrentPath().string().c_str());
  AppSettings settings;
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

  // TODO: Remove this and make it so it is loaded via a scene
  SceneManager::Instance().CreateObject<PlayerEntity>("Player");
  SceneManager::Instance().CreateObject<CameraFollowerEntity>("Follower");

  std::srand(static_cast<uint32>(std::time(nullptr)));
  for (int i = 0; i < 10; ++i)
  {
    SceneManager::Instance().CreateObject<EnemyEntity>(Utils::Format("Enemy_%d", i));
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

    // TODO: Add this to a debugtools manager or something like that
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
  rmt_UnbindOpenGL();
}