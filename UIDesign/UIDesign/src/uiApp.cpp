#include "uiApp.h"

#include "uiAudioSource.h"
#include "uiAudioListener.h"
#include "uiBullet.h"
#include "uiCamera.h"
#include "uiCameraFollower.h"
#include "uiEditorCamera.h"
#include "uiEnemy.h"
#include "uiFileSystem.h"
#include "uiInputManager.h"
#include "uiJSON.h"
#include "uiLogger.h"
#include "uiPhysics.h"
#include "uiPlayer.h"
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
  // TODO: Move this
  Thread* t;
  // Load Editor items instead of game
  if (m_parser.HasFlag("editor"))
  {
    m_splashScreen.Initialize();
    t = new Thread(&SplashScreen::Show, &m_splashScreen);
  }


  if (!StartSystems())
  {
    // Send systems error
    exit(403);
  }
  // t.join();
  if (!LoadResources())
  {
    // Send Resources error
  }

  if (m_parser.HasFlag("editor"))
  {
    m_splashScreen.m_loaded = true;
    t->join();
    m_splashScreen.ShutDown();
  }
}

bool App::StartSystems()
{
  Remotery* rmt;
  rmtError error = rmt_CreateGlobalInstance(&rmt);
  
  if (RMT_ERROR_NONE != error)
  {
    std::cout << "Error starting up Remotery " << error << std::endl;
    return false;
  }

  rmt_BindOpenGL();

  rmt_ScopedCPUSample(StartSystems, 0);

  Logger::StartUp();
  if (!Logger::IsStarted())
  {
    // You fucked up big time if you cant even dump your errors
  }
  Logger::Instance().AddOnLogAddedCallback(std::bind(&SplashScreen::SetLog, &m_splashScreen, std::placeholders::_1));


  ResourceManager::StartUp();
  if (!ResourceManager::IsStarted())
  {
    // Error loading Resource Manager
    Logger::Instance().AddLog("Error starting up resource manager", eLOGLEVEL::ERROR);
    return false;
  }
  Logger::Instance().AddLog("Started Resource Manager", eLOGLEVEL::DEFAULT, eLOGFLAG::SPLASH);
  
  InputManager::StartUp();
  if (!InputManager::IsStarted())
  {
    // Error loading Input Manager
    Logger::Instance().AddLog("Error starting up Input manager", eLOGLEVEL::ERROR);
    return false;
  }
  Logger::Instance().AddLog("Started Input Manager", eLOGLEVEL::DEFAULT, eLOGFLAG::SPLASH);
  
  SceneManager::StartUp();
  if (!SceneManager::IsStarted())
  {
    // Error loading Input Manager
    Logger::Instance().AddLog("Error starting up Scene manager", eLOGLEVEL::ERROR);
    return false;
  }
  Logger::Instance().AddLog("Started Scene Manager", eLOGLEVEL::DEFAULT, eLOGFLAG::SPLASH);

  Physics::StartUp();
  if (!Physics::IsStarted())
  {
    // Error loading Input Manager
    Logger::Instance().AddLog("Error starting up Physics manager", eLOGLEVEL::ERROR);
    return false;
  }
  Logger::Instance().AddLog("Started Physics Manager", eLOGLEVEL::DEFAULT, eLOGFLAG::SPLASH);

  WindowManager::StartUp();
  if (!WindowManager::IsStarted())
  {
    // Error loading Input Manager
    Logger::Instance().AddLog("Error starting up Window manager", eLOGLEVEL::ERROR);
    return false;
  }
  Logger::Instance().AddLog("Started Window Manager", eLOGLEVEL::DEFAULT, eLOGFLAG::SPLASH);

  UI::StartUp();
  if (!UI::IsStarted())
  {
    // Error loading Input Manager
    Logger::Instance().AddLog("Error starting up UI manager", eLOGLEVEL::ERROR);
    return false;
  }
  Logger::Instance().AddLog("Started UI Manager", eLOGLEVEL::DEFAULT, eLOGFLAG::SPLASH);

  if (m_parser.HasFlag("editor"))
  {
    
  }

  /************************************************************************/
  return true;
}

bool App::LoadResources()
{
  AppSettings settings;
  
  if (m_parser.HasFlag("editor"))
  {
    // TODO: Make this a dynamic load
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


    // TODO: Change location of this section
    String settingsPath = Utils::Format("%s/../resources/game.settings", FileSystem::CurrentPath().string().c_str());
    
    // TODO: Change this as this is only for testing
    SceneManager::Instance().CreateScene("TestScene");
    SceneManager::Instance().CreateScene("TestScene2");
    SceneManager::Instance().CreateScene("TestScene3");
    SceneManager::Instance().CreateScene("TestScene4");
    SceneManager::Instance().ChangeScene("TestScene");
    settings.FromFile(settingsPath);
  

    
  }
  else
  {
    Path workingDirPath = FileSystem::ExePath().parent_path();
    String packageStr = Utils::Format("%s/%s", workingDirPath.string().c_str(), "game.package");
    if (FileSystem::Exists(packageStr))
    {
      IFStream gamePackageFile(packageStr.c_str());
      JSONIStream isw(gamePackageFile);

      JSONDocument gameDoc;
      gameDoc.ParseStream(isw);

      // game settings
      JSONValue& settingsObj = gameDoc["settings"].GetObject();
      settings.m_gameName = settingsObj["gameName"].GetString();
      settings.m_displaySize = { settingsObj["resolutions"].GetArray()[0].GetArray()[0].GetUint(),
                                 settingsObj["resolutions"].GetArray()[0].GetArray()[1].GetUint() };
      settings.m_shouldUseVerticalSync = settingsObj["verticalSync"].GetBool();
      settings.m_framerate = settingsObj["framerate"].GetInt();

      // Resources
      ResourceManager::Instance().Deserialize(gameDoc["resources"]);

      // Scenes
      // JSONValue& scenesObj = .GetArray();
      SceneManager::Instance().Deserialize(gameDoc["sceneData"]);

    }
    else
    {
      // Throw error showing there is no package
      exit(404);
    }
  }
  WindowManager::Instance().Initialize(settings);
  UI::Instance().Initialize(WindowManager::Instance().m_mainWindow);

  if (m_parser.HasFlag("editor"))
  {
    m_editor = MakeUniqueObject<Editor>();
    m_editor->Initialize();
    // m_projectBuilder = MakeUniqueObject<ProjectBuilder>();
    // m_projectBuilder->Initialize();
    Logger::Instance().AddLog("Started Project Builder", eLOGLEVEL::DEFAULT, eLOGFLAG::SPLASH);
  }

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
  auto player = SceneManager::Instance().CreateObject<PlayerEntity>("Player");
  player->Move(Vector2f(500, 500));
  SceneManager::Instance().CreateObject<CameraFollowerEntity>("Follower");

  std::srand(static_cast<uint32>(std::time(nullptr)));
  for (int i = 0; i < 10; ++i)
  {
    SceneManager::Instance().CreateObject<EnemyEntity>(Utils::Format("Enemy_%d", i));
  }

  Clock deltaClock;
  Time dt;

  dt = deltaClock.restart();

  while (WindowManager::Instance().m_mainWindow.isOpen()) {
    InputManager::Instance().Update(dt.asMilliseconds());
    HEvent windowEvent;
    float delta = dt.asMilliseconds();
    float fps = 1000.0f / dt.asMilliseconds();
    while (WindowManager::Instance().m_mainWindow.pollEvent(windowEvent)) {
      ImGui::SFML::ProcessEvent(WindowManager::Instance().m_mainWindow, windowEvent);
      InputManager::Instance().PollEvents(windowEvent);
      if (windowEvent.type == HEvent::Closed) { WindowManager::Instance().m_mainWindow.close(); }
    }
    UI::Instance().Update(WindowManager::Instance().m_mainWindow, dt);

    // TODO: Add this to a debugtools manager or something like that
    if (InputManager::Instance().m_values[Input::eINPUTCODE::KeyCodeL][0]->GetState() == Input::eINPUTSTATE::PRESSED)
    {
      SceneManager::Instance().m_isDebug = !SceneManager::Instance().m_isDebug;
    }

    UI::Instance().GenerateIMGUI();

#if UI_EDITOR_MODE
    m_editor->Update(delta);
#endif
    // m_editor->m_camera.GetComponent<Camera>()->setSize(1200, 640);
    // m_editor->m_camera.SetPosition(Vector2f(0,0));
    // m_editor->m_camera.GetComponent<Camera>()->Update(delta);
    Physics::Instance().Update(10);
    SceneManager::Instance().Update(delta);

    WindowManager::Instance().Clear();

    SceneManager::Instance().UpdateRender(WindowManager::Instance().m_mainWindow);

    UI::Instance().Render(WindowManager::Instance().m_mainWindow);
    WindowManager::Instance().Display();

    dt = deltaClock.restart();
  }
}

void App::Exit()
{
  UI::Instance().Finish();
  rmt_UnbindOpenGL();
}