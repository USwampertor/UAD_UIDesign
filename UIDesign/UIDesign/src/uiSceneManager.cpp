#include "uiSceneManager.h"

#include "uiAnimator.h"
#include "uiApp.h"
#include "uiBoxCollider.h"
#include "uiJSON.h"
#include "uiSprite.h"

#include "uiClassRegisters.h"

#include "Remotery.h"

Scene* SceneManager::GetActiveScene()
{
  return m_activeScene.get();
}

Scene* SceneManager::CreateScene(const String& newSceneName)
{
  SharedPtr<Scene> newScene = MakeSharedObject<Scene>(newSceneName);
  newScene->Initialize();
  m_scenes.push_back(newScene);
  return newScene.get();
}

bool SceneManager::ChangeScene(const String& sceneToLoad)
{
  if (m_activeScene)
  {
    m_activeScene->OnSceneUnload();
  }
  for (const SharedPtr<Scene>& s : m_scenes)
  {
    if (s->m_sceneName == sceneToLoad)
    {
      m_activeScene = s;
      m_activeScene->OnSceneLoaded();
      return true;
    }
  }
  return false;
}

Scene* SceneManager::LoadScene(const String& newSceneName)
{
  Scene* s = nullptr;

  return s;
}

void SceneManager::SaveScene()
{

}

Scene* SceneManager::FindScene(const String& sceneToFind)
{
  for (int i = 0; i < m_scenes.size(); ++i)
  {
    if (m_scenes[i]->m_sceneName == sceneToFind)
    {
      return m_scenes[i].get();
    }
  }
  return nullptr;
}

void SceneManager::Update(const float& delta)
{
  // rmt_ScopedCPUSample(Update, 0);
  // Delete Entities that are marked for delete
  for (Entity* toDelete : m_activeScene->m_toRemove)
  {
    int i = 0;

    for (SharedPtr<Entity>& e : m_activeScene->m_entities)
    {
      if (e.get() == toDelete)
      {
        //
        e->OnDestroy();
        e.reset();
        m_activeScene->m_entities.erase(m_activeScene->m_entities.begin() + i);
        break;
      }
      ++i;
    }
    m_activeScene->m_toRemove.clear();
  }

  for (int j = 0; j < m_activeScene->m_entities.size(); ++j)
  {
    // TODO: Check a better way of doing this
    if (!App::Instance().m_parser.HasFlag("editor"))
    {
      m_activeScene->m_entities[j]->Update(delta);
    }

  }
}

void SceneManager::UpdateRender(sf::RenderWindow& w)
{
  // rmt_ScopedCPUSample(UpdateRender, 0);
  for (int i = 0; i < SceneManager::Instance().GetActiveScene()->m_entities.size(); ++i)
  {
    
    if (m_activeScene->m_entities[i]->GetComponent<Sprite>())
    {
      w.draw(*m_activeScene->m_entities[i]->GetComponent<Sprite>());
    }
    if (m_activeScene->m_entities[i]->GetComponent<BoxCollider>() && m_isDebug)
    {
      w.draw(*m_activeScene->m_entities[i]->GetComponent<BoxCollider>());
      w.draw(*m_activeScene->m_entities[i]->m_gizmoSprite);
    }
  }
}

JSONDocument SceneManager::Serialize(const Vector<String>& names)
{
  JSONDocument document;
  document.SetArray();
  JSONDocument::AllocatorType& allocator = document.GetAllocator();

  for (const auto& name : names)
  {
    JSONValue obj(rapidjson::kObjectType);

    Scene* sceneToSave = FindScene(name);
    obj.AddMember("sceneName", sceneToSave->m_sceneName, allocator);
    obj.AddMember("gameSettings", sceneToSave->m_settings->m_gameSettings, allocator);
    
    JSONValue gravity(rapidjson::kArrayType);
    gravity.PushBack(sceneToSave->m_settings->m_levelGravity.x, allocator);
    gravity.PushBack(sceneToSave->m_settings->m_levelGravity.y, allocator);
    obj.AddMember("gravity", gravity, allocator);

    JSONValue entitiesDoc(rapidjson::kArrayType);
    for (int i = 0; i < sceneToSave->m_entities.size(); ++i)
    {
      JSONDocument entityDoc = sceneToSave->m_entities[i]->Serialize();
      entitiesDoc.PushBack(JSONValue(entityDoc, allocator), allocator);
    }
    obj.AddMember("entityData", entitiesDoc, allocator);

    document.PushBack(obj, allocator);
  }
  return document;

}

void SceneManager::Deserialize(const JSONValue& sceneArray)
{
  for (auto& itr : sceneArray.GetArray())
  {
    // String sceneName = itr.GetObject()["sceneName"].GetString();
    auto obj = itr.GetObject();
    String sceneName = obj["sceneName"].GetString();
    String gameSettings = obj["gameSettings"].GetString();
    
    Vector2f gravity;
    // JSONValue gravityObj = obj["gravity"].GetArray()[0];
    gravity.x = obj["gravity"].GetArray()[0].GetFloat();
    gravity.y = obj["gravity"].GetArray()[1].GetFloat();
    
    Scene* newScene = CreateScene(sceneName);
    newScene->m_settings->m_levelGravity = gravity;
    newScene->m_settings->m_gameSettings = gameSettings;
    
    // JSONValue entityData = obj["entityData"].GetArray();
    
    for (auto& entity : obj["entityData"].GetArray())
    {
      SharedPtr<Entity> e = ClassRegisters::CreateEntity(entity["type"].GetString());
      newScene->m_entities.push_back(e);
    }
  }
  m_activeScene = m_scenes[0];
}