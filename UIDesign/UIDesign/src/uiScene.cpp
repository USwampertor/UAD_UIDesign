#include "uiScene.h"


JSONDocument Scene::Serialize()
{
  JSONDocument scene;

  JSONValue entities(rapidjson::kObjectType);

  for (int i = 0; i < m_entities.size(); ++i)
  {
  }

  return scene;
}