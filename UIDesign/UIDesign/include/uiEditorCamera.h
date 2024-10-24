#pragma once
#include "uiPrerequisites.h"
#include "uiEntity.h"

// No uiClassRegisters.h file as this should not be able to be instantiable except
// by editor

class Camera;

class EditorCameraEntity : public Entity
{
public:
  static String GetType() { return "EditorCameraEntity"; }

  EditorCameraEntity() : Entity("EditorCamera") {}

  virtual void Initialize() override;

  virtual void Update(const float& deltaMS) override;

  void SetToAvailableArea();

  Camera* m_camera = nullptr;

  float m_cameraMoveSpeed;
  float m_cameraZoomSpeed;
};

