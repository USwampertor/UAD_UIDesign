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
#include "uiProjectBuilder.h"
#include "uiResourceManager.h"
#include "uiSceneManager.h"
#include "uiUI.h"
#include "uiTexture.h"
#include "uiWindowManager.h"


#include "imgui.h"
#include "imgui-SFML.h"
#include "imgui_stdlib.h"
#include "Remotery.h"



void App::OnStartUp()
{
  m_splashScreen.Initialize();
  // Thread t(&SplashScreen::Show, &m_splashScreen);


  // TODO: Move this
  m_parser.AddFlag("editor");
  m_parser.SetFlag("editor", "true");

  // Load Editor instead of game
  if (m_parser.GetFlag("editor") == "true")
  {
    
  }


  if (!StartSystems())
  {
    // Send systems error
    m_splashScreen.m_loaded = true;
    exit(403);
  }
  // t.join();
  if (!LoadResources())
  {
    // Send Resources error
    m_splashScreen.m_loaded = true;
  }
  m_splashScreen.m_loaded = true;
}

bool App::StartSystems()
{
  m_splashScreen.SetTaskString("Loading Systems");
  m_splashScreen.SetTaskString("Setting up Remotery");
  Remotery* rmt;
  rmtError error = rmt_CreateGlobalInstance(&rmt);
  
  if (RMT_ERROR_NONE != error)
  {
    std::cout << "Error starting up Remotery" << std::endl;
    return false;
  }

  m_splashScreen.SetTaskString("Binding up Remotery for OpenGL");
  rmt_BindOpenGL();

  rmt_ScopedCPUSample(StartSystems, 0);

  m_splashScreen.SetTaskString("Setting up Resource Manager");
  ResourceManager::StartUp();
  if (!ResourceManager::IsStarted())
  {
    // Error loading Resource Manager
    std::cout << "Error starting up resource manager" << std::endl;
    return false;
  }
  else
  {
    m_splashScreen.SetTaskString("Resource Manager working correctly");
    std::cout << "Resource Manager working correctly" << std::endl;
  }
  m_splashScreen.SetTaskString("Setting up Input Manager");
  InputManager::StartUp();
  if (!InputManager::IsStarted())
  {
    // Error loading Input Manager
    return false;
  }
  m_splashScreen.SetTaskString("Setting up Scene Manager");
  SceneManager::StartUp();
  if (!SceneManager::IsStarted())
  {
    // Error loading Scene Manager
    return false;
  }
  m_splashScreen.SetTaskString("Setting up Physics Manager");
  Physics::StartUp();
  if (!Physics::IsStarted())
  {
    // Error loading Physics
    return false;
  }
  m_splashScreen.SetTaskString("Setting up Window Manager Manager");
  WindowManager::StartUp();
  if (!WindowManager::IsStarted())
  {
    // Error loading Window Manager
    return false;
  }
  m_splashScreen.SetTaskString("Setting up UI Manager");
  UI::StartUp();
  if (!UI::IsStarted())
  {
    // Error loading UI
    return false;
  }

  if (m_parser.GetFlag("editor") == "true")
  {
    m_splashScreen.SetTaskString("Setting up ProjectBuilder");
    m_projectBuilder = MakeUniqueObject<ProjectBuilder>();
  }

  /************************************************************************/
  m_splashScreen.SetTaskString("Everything finished correctly");
  return true;
}

bool App::LoadResources()
{
  m_splashScreen.SetTaskString("Loading Resources");
  ResourceManager::Instance().LoadResource<Texture>(Utils::Format("%s/../resources/gizmo.png", FileSystem::CurrentPath().string().c_str()));
  String atlasPath1 = Utils::Format("%s/../resources/sprite1.json", FileSystem::CurrentPath().string().c_str());
  m_splashScreen.SetTaskString(Utils::Format("Loading %s", atlasPath1.c_str()));
  ResourceManager::Instance().LoadResource<Atlas>(atlasPath1);
  ResourceManager::Instance().CreateResource<Animation>("idleEnemy");
  ResourceManager::Instance().GetResource<Animation>("idleEnemy")->Initialize(ResourceManager::Instance().GetResource<Atlas>("sprite1")->m_atlas, 400.0f);
  ResourceManager::Instance().GetResource<Animation>("idleEnemy")->SetLoop(true);
  String atlasPath2 = Utils::Format("%s/../resources/sprite2.json", FileSystem::CurrentPath().string().c_str());
  m_splashScreen.SetTaskString(Utils::Format("Loading %s", atlasPath2.c_str()));
  ResourceManager::Instance().LoadResource<Atlas>(atlasPath2);
  ResourceManager::Instance().CreateResource<Animation>("idleBullet");
  ResourceManager::Instance().GetResource<Animation>("idleBullet")->Initialize(ResourceManager::Instance().GetResource<Atlas>("sprite2")->m_atlas, 400.0f);
  ResourceManager::Instance().GetResource<Animation>("idleBullet")->SetLoop(true);
  String playerPath = Utils::Format("%s/../resources/player.json", FileSystem::CurrentPath().string().c_str());
  m_splashScreen.SetTaskString(Utils::Format("Loading %s", playerPath.c_str()));
  ResourceManager::Instance().LoadResource<Atlas>(playerPath);
  ResourceManager::Instance().CreateResource<Animation>("idlePlayer");
  ResourceManager::Instance().GetResource<Animation>("idlePlayer")->Initialize(ResourceManager::Instance().GetResource<Atlas>("player")->m_atlas, 800.0f);
  ResourceManager::Instance().GetResource<Animation>("idlePlayer")->SetLoop(true);
  String playerWalkingPath = Utils::Format("%s/../resources/playerwalking.json", FileSystem::CurrentPath().string().c_str());
  m_splashScreen.SetTaskString(Utils::Format("Loading %s", playerWalkingPath.c_str()));
  ResourceManager::Instance().LoadResource<Atlas>(playerWalkingPath);
  ResourceManager::Instance().CreateResource<Animation>("walkingPlayer");
  ResourceManager::Instance().GetResource<Animation>("walkingPlayer")->Initialize(ResourceManager::Instance().GetResource<Atlas>("playerwalking")->m_atlas, 400.0f);
  ResourceManager::Instance().GetResource<Animation>("walkingPlayer")->SetLoop(true);

  String audioPath = Utils::Format("%s/../resources/pingas.mp3", FileSystem::CurrentPath().string().c_str());
  ResourceManager::Instance().LoadResource<AudioClip>(audioPath);
  String audioPath2 = Utils::Format("%s/../resources/ping.mp3", FileSystem::CurrentPath().string().c_str());
  ResourceManager::Instance().LoadResource<AudioClip>(audioPath2);
  ResourceManager::Instance().LoadResource<AudioClip>(Utils::Format("%s/../resources/fart.mp3", FileSystem::CurrentPath().string().c_str()));


  // TODO: Change location of this section
  String settingsPath = Utils::Format("%s/../resources/game.settings", FileSystem::CurrentPath().string().c_str());
  AppSettings settings;
  settings.FromFile(settingsPath);
  WindowManager::Instance().Initialize(settings);
  UI::Instance().Initialize(*WindowManager::Instance().m_mainWindow.get());


  SceneManager::Instance().CreateScene("TestScene");
  SceneManager::Instance().CreateScene("TestScene2");
  SceneManager::Instance().CreateScene("TestScene3");
  SceneManager::Instance().CreateScene("TestScene4");
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

    UI::Instance().GenerateIMGUI();

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