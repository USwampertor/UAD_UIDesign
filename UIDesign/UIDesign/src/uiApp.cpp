#include "uiApp.h"

#include "uiInputManager.h"
#include "uiPhysics.h"
#include "uiResourceManager.h"
#include "uiSceneManager.h"

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
  return true;
}

bool App::LoadResources()
{
  String atlasPath1 = Utils::Format("%s/../resources/sprite1.json", FileSystem::CurrentPath().string().c_str());
  SharedPtr<Atlas> atlas1 = ResourceManager::Instance().LoadResource<Atlas>(atlasPath1);
  SharedPtr<Animation> animation1 = ResourceManager::Instance().CreateResource<Animation>("idleEnemy");
  String atlasPath2 = Utils::Format("%s/../resources/sprite2.json", FileSystem::CurrentPath().string().c_str());
  SharedPtr<Atlas> atlas2 = ResourceManager::Instance().LoadResource<Atlas>(atlasPath2);
  SharedPtr<Animation> animation2 = ResourceManager::Instance().CreateResource<Animation>("idleBullet");
  String audioPath = Utils::Format("%s/../resources/pingas.mp3", FileSystem::CurrentPath().string().c_str());

  return true;
}

void App::Run()
{
  Update();
  Exit();
}

void App::Update()
{

}

void App::Exit()
{

}