#include "uiSceneManager.h"

#include "uiAnimator.h"
#include "uiApp.h"
#include "uiBoxCollider.h"
#include "uiSprite.h"

#include "uiClassRegisters.h"

#include "Remotery.h"

Scene* SceneManager::GetActiveScene()
{
  return m_activeScene.get();
}

Scene* SceneManager::CreateScene(const String& newSceneName)
{
  SharedPtr<Scene> newScene = MakeSharedObject<Scene>(newSceneName);
  newScene->Initialize();
  m_scenes.push_back(newScene);
  return newScene.get();
}

bool SceneManager::ChangeScene(const String& sceneToLoad)
{
  if (m_activeScene)
  {
    m_activeScene->OnSceneUnload();
  }
  for (const SharedPtr<Scene>& s : m_scenes)
  {
    if (s->m_sceneName == sceneToLoad)
    {
      m_activeScene = s;
      m_activeScene->OnSceneLoad();
      return true;
    }
  }
  return false;
}

Scene* SceneManager::LoadScene(const String& newSceneName)
{
  Scene* s = nullptr;

  return s;
}

void SceneManager::SaveScene()
{

}

void SceneManager::Update(const float& delta)
{
  rmt_ScopedCPUSample(Update, 0);
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

  for (int j = 0; j < m_activeScene->m_entities.size(); ++j)
  {
    // TODO: Check a better way of doing this
    if (App::Instance().m_parser.GetFlag("editor") != "true")
    {
      m_activeScene->m_entities[j]->Update(delta);
    }

  }
}

void SceneManager::UpdateRender(sf::RenderWindow& w)
{
  rmt_ScopedCPUSample(UpdateRender, 0);
  for (int i = 0; i < SceneManager::Instance().GetActiveScene()->m_entities.size(); ++i)
  {
    
    if (m_activeScene->m_entities[i]->GetComponent<Sprite>())
    {
      w.draw(*m_activeScene->m_entities[i]->GetComponent<Sprite>());
    }
    if (m_activeScene->m_entities[i]->GetComponent<BoxCollider>() && m_isDebug)
    {
      w.draw(*m_activeScene->m_entities[i]->GetComponent<BoxCollider>());
      w.draw(*m_activeScene->m_entities[i]->m_gizmoSprite);
    }
  }
}

