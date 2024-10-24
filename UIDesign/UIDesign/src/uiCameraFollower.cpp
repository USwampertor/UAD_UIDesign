#include "uiCameraFollower.h"

#include "uiAudioSource.h"
#include "uiBoid.h"
#include "uiCamera.h"
#include "uiResourceManager.h"
#include "uiSceneManager.h"
#include "uiWindowManager.h"

void CameraFollowerEntity::Initialize()
{
  Entity::Initialize();
  Vector2f s(WindowManager::Instance().m_mainWindow.getSize().x, WindowManager::Instance().m_mainWindow.getSize().y);
  m_camera = CreateComponent<Camera>(Vector2f(0, 0), s);
  m_source = CreateComponent<AudioSource>();
  m_source->SetClip(ResourceManager::Instance().GetResource<AudioClip>("fart"));
}

void CameraFollowerEntity::Update(const float& delta)
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

JSONDocument CameraFollowerEntity::Serialize()
{
  JSONDocument d = Entity::Serialize();
  JSONDocument::AllocatorType& allocator = d.GetAllocator();
  if (d.HasMember("type"))
  {
    d["type"].SetString(GetType().c_str(), allocator);
  }
  else
  {
    JSONValue v;
    v.SetString(GetType().c_str(), allocator);
    d.AddMember("type", v, allocator);
  }
  return d;
}

