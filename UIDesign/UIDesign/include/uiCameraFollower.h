#pragma once

#include "uiPrerequisites.h"

#include "uiEntity.h"

#include "uiCamera.h"

class CameraFollower : public Entity
{
public:
  CameraFollower() = default;

  CameraFollower(const String& name) : Entity(name)
  {
    m_camera = CreateComponent<Camera>();
  }

  Camera* m_camera;
};

