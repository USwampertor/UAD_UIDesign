#include "uiCameraFollower.h"

#include "uiAudioSource.h"
#include "uiResourceManager.h"
#include "uiSceneManager.h"

void CameraFollower::Initialize()
{
  Entity::Initialize();
  Vector2f s(WindowManager::Instance().m_mainWindow->getSize().x, WindowManager::Instance().m_mainWindow->getSize().y);
  m_camera = CreateComponent<Camera>(Vector2f(0, 0), s);
  m_source = CreateComponent<AudioSource>();
  m_source->SetClip(ResourceManager::Instance().GetResource<AudioClip>("fart"));
}

