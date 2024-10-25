#pragma once
#include "uiPrerequisites.h"
#include "uiClassRegisters.h"

#include "uiEntity.h"

class AudioSource;
class Camera;

class CameraFollowerEntity : public Entity
{
public:

  static String GetType() { return "CameraFollowerEntity"; }

  CameraFollowerEntity() = default;

  CameraFollowerEntity(const String& name) : Entity(name) {}

  virtual void Initialize() override;

  virtual void Update(const float& delta) override;

  virtual JSONDocument Serialize() override;

  Camera* m_camera = nullptr;
  AudioSource* m_source = nullptr;
};

REGISTER_CLASS(CameraFollowerEntity)
