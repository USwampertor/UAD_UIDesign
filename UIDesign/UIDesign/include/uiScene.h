
#pragma once

#include "uiPrerequisites.h"

#include "uiUtilities.h"
#include "uiEntity.h"

#include "uiSceneSettings.h"

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

  UniquePtr<SceneSettings>& GetSettings();

  // UniquePtr<Entity> m_root;

  Vector<SharedPtr<Entity>> m_entities;

  UniquePtr<SceneSettings> m_settings;

  String m_sceneName;
};

