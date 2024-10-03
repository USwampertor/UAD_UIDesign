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

  bool ChangeScene(const String& sceneToLoad);

  void Update(const float& delta)
  {
    // Delete Entities that are marked for delete
    for (Entity* toDelete : m_activeScene->m_toRemove)
    {
      int i = 0;

      for (SharedPtr<Entity>& e : m_activeScene->m_entities)
      {
        if (e.get() == toDelete)
        {
          //
          e->OnDestroy();
          e.reset();
          m_activeScene->m_entities.erase(m_activeScene->m_entities.begin() + i);
          break;
        }
        ++i;
      }
      m_activeScene->m_toRemove.clear();
    }

    // for (Vector<SharedPtr<Entity>>::iterator it = m_activeScene->m_entities.begin();
    //   it != m_activeScene->m_entities.end();
    //   ++it)
    // {
    for(int j = 0; j < m_activeScene->m_entities.size(); ++j)
    {
    // for (const SharedPtr<Entity>& e : m_activeScene->m_entities)
    // {
      // if (it)
      // Entity* e = (*it).get();
      m_activeScene->m_entities[j]->Update(delta);

    }
  }

  void UpdateRender(sf::RenderWindow& w);
  

  Scene* GetActiveScene();

  SharedPtr<Scene> m_activeScene;

  Vector<SharedPtr<Scene>> m_scenes;

  bool m_isDebug = false;
};

