#pragma once
#include "uiPrerequisites.h"

#include "uiModule.h"
#include "uiScene.h"

// TODO: Change this to another location
#include <SFML/Graphics/RenderWindow.hpp>

class SceneManager : public Module<SceneManager>
{
public:
  template <typename T,
            typename = std::enable_if_t<std::is_base_of<Entity, T>::value>>
            void DestroyObject(T* toDelete)
  {
    toDelete->m_markedToDestroy = true;
    m_activeScene->m_toRemove.push_back(toDelete);
    
  }

  template <typename T,
            typename = std::enable_if_t<std::is_base_of<Entity, T>::value>,
            typename... Args>
  T* CreateObject(Args ... args)
  {
    SharedPtr<T> newEntity = MakeSharedObject<T>(std::forward<Args>(args)...);
    newEntity->Initialize();
    m_activeScene->m_entities.push_back(newEntity);
    return newEntity.get();
  }

  template <typename T,
            typename = std::enable_if_t<std::is_base_of<Entity, T>::value>>
  T* FindObject(const String& toFind)
  {
    int i = 0;
    for (const SharedPtr<Entity>& e : m_activeScene->m_entities)
    {
      if (e->GetName() == toFind && !e->m_markedToDestroy)
      {
        return static_cast<T*>(e.get());
      }
      ++i;
    }
    return nullptr;
  }

  Scene* CreateScene(const String& newSceneName);

  Scene* LoadScene(const String& newSceneName);

  Scene* UnloadScene(const String& sceneToUnload);

  Scene* FindScene(const String& sceneToFind);

  bool ChangeScene(const String& sceneToLoad);

  void SaveScene();

  void Update(const float& delta);

  void UpdateRender(sf::RenderWindow& w);
  
  Scene* GetActiveScene();

  SharedPtr<Scene> m_activeScene;

  Vector<SharedPtr<Scene>> m_scenes;

  bool m_isDebug = false;
};

