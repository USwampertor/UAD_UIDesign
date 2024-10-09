
#pragma once

#include "uiPrerequisites.h"

#include "uiEntity.h"
#include "uiSceneSettings.h"
#include "uiJSON.h"

class Scene
{
public:

  Scene() = default;

  ~Scene() = default;

  Scene(const String& newName)
  {
    m_sceneName = newName;
  }

  void Initialize()
  {
    // m_root = MakeUniqueObject<Entity>();
    // m_root->Initialize();
    m_entities.clear();
  }

  void OnSceneUnload()
  {

  }

  void OnSceneLoad()
  {

  }

  JSONDocument Serialize();

  void Deserialize();

  UniquePtr<SceneSettings>& GetSettings();

  // UniquePtr<Entity> m_root;

  Vector<SharedPtr<Entity>> m_entities;

  Vector<Entity*> m_toRemove;

  UniquePtr<SceneSettings> m_settings;

  String m_sceneName;
};

