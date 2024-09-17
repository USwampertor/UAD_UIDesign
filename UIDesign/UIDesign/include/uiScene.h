
#pragma once

#include "uiPrerequisites.h"

#include "uiUtilities.h"
#include "uiEntity.h"

#include "uiSceneSettings.h"

class Scene
{
public:

  template <typename T
            typename = std::enable_if_t<std::is_base_of<Entity, T>::value>>
  void DestroyObject(T* toDelete)
  {

  }

  template <typename T
            typename = std::enable_if_t<std::is_base_of<Entity, T>::value>>
  SharedPtr<T>& FindEntity(T* toFind)
  {


    for (const T& obj : m_root->Children())
    {

    }
  }
  
  template <typename T, 
            typename = std::enable_if_t<std::is_base_of<Entity, T>::value>,
            typename... Args>
  T* MakeNew(Args ... args)
  {
    SharedPtr<T> newEntity = MakeSharedObject<T>(std::forward<Args>(args)...);
    m_root.push_back(newEntity);
    return newEntity.get();
  }

  void Initialize()
  {
    m_root = MakeUniqueObject<Entity>();
    m_root->Initialize();
  }

  UniquePtr<SceneSettings>& GetSettings();

  UniquePtr<Entity> m_root;

  void AddToScene(SharedPtr<Entity> newEntity);

  UniquePtr<SceneSettings> m_settings;

  String m_sceneName;
};

