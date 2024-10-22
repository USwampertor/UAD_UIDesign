#include "uiScene.h"

void Scene::Initialize()
{
  m_entities.clear();
  m_settings = MakeUniqueObject<SceneSettings>();
}

JSONDocument Scene::Serialize()
{
  JSONDocument sceneDocument;
  sceneDocument.SetObject();
  JSONDocument::AllocatorType& allocator = sceneDocument.GetAllocator();
  // 
  JSONValue sceneSettingsValue(rapidjson::kObjectType);
  // 
  sceneSettingsValue.AddMember("gameSettings", m_settings->m_gameSettings, allocator);
  
  // JSONValue gravityArray;
  // gravityArray.SetArray();
  // gravityArray.PushBack(0.0f, allocator);
  // gravity.PushBack(1, allocator);
  sceneSettingsValue.AddMember("gravityX", m_settings->m_levelGravity.x, allocator);
  sceneSettingsValue.AddMember("gravityY", m_settings->m_levelGravity.y, allocator);
   
  // 
  sceneDocument.AddMember("sceneSettings", sceneSettingsValue, allocator);
  // 
  // JSONValue entitiesArray(rapidjson::kArrayType);
  // 
  // for (int i = 0; i < m_entities.size(); ++i)
  // {
  //   JSONDocument entity = m_entities[i]->Serialize();
  //   entitiesArray.PushBack(std::move(entity), allocator);
  // }
  // 
  // sceneDocument.AddMember("entities", entitiesArray, allocator);

  return sceneDocument;
}

void Scene::Deserialize(const JSONDocument& d)
{
  const JSONValue& gravity = d["sceneSettings"]["gravity"];
}