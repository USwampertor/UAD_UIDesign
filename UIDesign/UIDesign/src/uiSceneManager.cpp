#include "uiSceneManager.h"

#include "uiAnimator.h"
#include "uiBoxCollider.h"

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

void SceneManager::UpdateRender(sf::RenderWindow& w)
{
  for (int i = 0; i < SceneManager::Instance().GetActiveScene()->m_entities.size(); ++i)
  {
    
    if (m_activeScene->m_entities[i]->GetComponent<BoxCollider>() && m_isDebug)
    {
      w.draw(*m_activeScene->m_entities[i]->GetComponent<BoxCollider>());
    }
    if (m_activeScene->m_entities[i]->GetComponent<Animator>())
    {
      w.draw(m_activeScene->m_entities[i]->GetComponent<Animator>()->GetSprite());
    }
  }
}