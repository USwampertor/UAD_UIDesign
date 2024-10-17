#include "uiScene.h"

void Scene::Initialize()
{
  m_entities.clear();
  m_settings = MakeUniqueObject<SceneSettings>();
}

JSONDocument Scene::Serialize()
{
  JSONDocument sceneDocument;
  JSONDocument::AllocatorType& allocator = sceneDocument.GetAllocator();

  JSONValue sceneSettingsValue(rapidjson::kObjectType);

  JSONValue gravity(rapidjson::kArrayType);
  gravity.PushBack(m_settings->m_levelGravity.x, allocator);
  gravity.PushBack(m_settings->m_levelGravity.y, allocator);
  sceneSettingsValue.AddMember("gravity", gravity, allocator);
  JSONValue gameSettings;
  gameSettings.SetString(m_settings->m_gameSettings, allocator);
  sceneSettingsValue.AddMember("gameSettings", gameSettings, allocator);


  sceneDocument.AddMember("sceneSettings", sceneSettingsValue, allocator);

  JSONValue entitiesArray(rapidjson::kArrayType);

  for (int i = 0; i < m_entities.size(); ++i)
  {
    entitiesArray.PushBack(std::move(m_entities[i]->Serialize()), allocator);
  }

  sceneDocument.AddMember("entities", entitiesArray, allocator);

  return sceneDocument;
}

void Scene::Deserialize(const JSONDocument& d)
{
  const JSONValue& gravity = d["sceneSettings"]["gravity"];
}