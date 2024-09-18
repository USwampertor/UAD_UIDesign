#pragma once
#include "uiPrerequisites.h"

#include "uiModule.h"
#include "uiScene.h"

#include <SFML/Window.hpp>

class SceneManager : public Module<SceneManager>
{
public:
  template <typename T,
            typename = std::enable_if_t<std::is_base_of<Entity, T>::value>>
            void DestroyObject(T* toDelete)
  {
    int i = 0;
    for (SharedPtr<Entity>& e : m_activeScene->m_entities)
    {
      if (e.get() == toDelete)
      {
        e.reset();
        m_activeScene->m_entities.erase(m_activeScene->m_entities.begin() + i);
        break;
      }
      ++i;
    }
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
      if (e->GetName() == toFind)
      {
        return e.get();
      }
      ++i;
    }
  }

  Scene* CreateScene(const String& newSceneName);

  bool ChangeScene(const String& sceneToLoad);

  void Update(const float& delta)
  {
    for (const SharedPtr<Entity>& e : m_activeScene->m_entities)
    {
      e->Update(delta);
    }
  }

  void UpdateRender(sf::RenderWindow& w);
  

  Scene* GetActiveScene();

  SharedPtr<Scene> m_activeScene;

  Vector<SharedPtr<Scene>> m_scenes;

  bool m_isDebug = false;
};

