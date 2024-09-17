#pragma once
#include "uiPrerequisites.h"

#include "uiModule.h"
#include "uiScene.h"


class SceneManager : public Module<SceneManager>
{

  bool LoadScene(const String& sceneToLoad);

  SharedPtr<Scene> m_activeScene;

  Vector<SharedPtr<Scene>> m_scenes;
};

