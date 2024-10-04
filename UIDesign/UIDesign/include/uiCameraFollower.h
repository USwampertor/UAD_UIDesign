#pragma once

#include "uiPrerequisites.h"

#include "uiEntity.h"

class AudioSource;
class Camera;

class CameraFollower : public Entity
{
public:
  CameraFollower() = default;

  CameraFollower(const String& name) : Entity(name) {}

  virtual void Initialize() override;

  virtual void Update(const float& delta) override;

  Camera* m_camera = nullptr;
  AudioSource* m_source = nullptr;
};

