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
  sceneDocument.AddMember("sceneName", m_sceneName, allocator);
  return sceneDocument;
}

void Scene::Deserialize(const JSONDocument& d)
{
  const JSONValue& gravity = d["sceneSettings"]["gravity"];
}