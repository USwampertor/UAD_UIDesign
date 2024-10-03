#pragma once

#include "uiPrerequisites.h"

#include "uiEntity.h"

#include "uiCamera.h"

#include "uiBoid.h"
#include "uiSceneManager.h"
#include "uiWindowManager.h"

class AudioSource;

class CameraFollower : public Entity
{
public:
  CameraFollower() = default;

  CameraFollower(const String& name) : Entity(name) {}

  virtual void Initialize() override;

  virtual void Update(const float& delta) override
  {
    Entity::Update(delta);
    Entity* player = SceneManager::Instance().FindObject<Entity>("Player");
    if (player != nullptr)
    {
      Vector2f speed = Boid::Approach(GetTransform().position, player->GetTransform().position, 150, 10) * (delta /1000);
      Move(speed);
      Rotate(delta);
    }
  }

  Camera* m_camera = nullptr;
  AudioSource* m_source = nullptr;
};

