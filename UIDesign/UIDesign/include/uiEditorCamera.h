#pragma once
#include "uiPrerequisites.h"
#include "uiEntity.h"
#include "uiVector2.h"
#include "uiShader.h"

// No uiClassRegisters.h file as this should not be able to be instantiable except
// by editor

class Camera;
class ImGuiDockNode;
class Sprite;

class EditorCameraEntity : public Entity
{
public:
  static String GetType() { return "EditorCameraEntity"; }

  EditorCameraEntity() : Entity("EditorCamera") {}

  virtual void Initialize() override;

  virtual void Update(const float& deltaMS) override;

  void SetToAvailableArea();

  Camera* m_camera = nullptr;
  Sprite* m_grid = nullptr;
  Shader* m_gridShader = nullptr;
  ImGuiDockNode* m_centralNode = nullptr;
  float m_cameraMoveSpeed = 15;
  float m_cameraZoomSpeed = 15;
  float m_cameraActualZoom = 1.0f;
};

