#include "uiCameraFollower.h"

#include "uiAudioSource.h"
#include "uiBoid.h"
#include "uiCamera.h"
#include "uiResourceManager.h"
#include "uiSceneManager.h"
#include "uiWindowManager.h"

void CameraFollower::Initialize()
{
  Entity::Initialize();
  Vector2f s(WindowManager::Instance().m_mainWindow->getSize().x, WindowManager::Instance().m_mainWindow->getSize().y);
  m_camera = CreateComponent<Camera>(Vector2f(0, 0), s);
  m_source = CreateComponent<AudioSource>();
  m_source->SetClip(ResourceManager::Instance().GetResource<AudioClip>("fart"));
}

void CameraFollower::Update(const float& delta)
{
  Entity::Update(delta);
  Entity* player = SceneManager::Instance().FindObject<Entity>("Player");
  if (player != nullptr)
  {
    Vector2f speed = Boid::Approach(GetTransform().position, player->GetTransform().position, 150, 10) * (delta / 1000);
    Move(speed);
    Rotate(delta);
  }
}