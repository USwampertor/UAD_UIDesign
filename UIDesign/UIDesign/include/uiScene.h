
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

  void Initialize();

  void OnSceneUnload()
  {

  }

  void OnSceneLoaded()
  {

  }

  JSONDocument Serialize();

  void Deserialize(const JSONDocument& d);

  UniquePtr<SceneSettings>& GetSettings();

  // UniquePtr<Entity> m_root;

  Vector<SharedPtr<Entity>> m_entities;

  Vector<Entity*> m_toRemove;

  UniquePtr<SceneSettings> m_settings;

  String m_sceneName;
};

