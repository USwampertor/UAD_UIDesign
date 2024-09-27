#pragma once

#include "uiPrerequisites.h"

#include "uiEntity.h"

#include "uiCamera.h"

#include "uiBoid.h"
#include "uiSceneManager.h"
#include "uiWindowManager.h"

class CameraFollower : public Entity
{
public:
  CameraFollower() = default;

  CameraFollower(const String& name) : Entity(name)
  {
    
  }

  virtual void Initialize() override
  {
    Entity::Initialize();
    Vector2f s(WindowManager::Instance().m_mainWindow->getSize().x, WindowManager::Instance().m_mainWindow->getSize().y);
    m_camera = CreateComponent<Camera>(Vector2f(0,0), s);
  }

  virtual void Update(const float& delta) override
  {
    Entity::Update(delta);
    Vector2f speed = Boid::Approach(GetTransform().position, SceneManager::Instance().FindObject<Entity>("Player")->GetTransform().position, 150, 10) * (delta /1000);
    Move(speed);
    Rotate(delta * 0.001);
  }

  Camera* m_camera = nullptr;
};

