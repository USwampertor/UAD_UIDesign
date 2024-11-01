#pragma once
#include "uiPrerequisites.h"
// #include "uiClassRegisters.h"

#include "uiController.h"
#include "uiInputMapping.h"


class EditorCameraEntity;
class CameraFollowerEntity;

class EditorControllerEntity : public ControllerEntity
{
public:
  static String GetType() { return "EditorControllerEntity"; }

  EditorControllerEntity() = default;
  
  EditorControllerEntity(const String& newName) : ControllerEntity(newName) {}

  ~EditorControllerEntity() = default;

  virtual void Initialize() override;

  virtual void Update(const float& deltaMS) override;

  void MoveCameraUp(SharedPtr<InputValue> value);
  void MoveCameraDown(SharedPtr<InputValue> value);
  void MoveCameraLeft(SharedPtr<InputValue> value);
  void MoveCameraRight(SharedPtr<InputValue> value);
  void Zoom(SharedPtr<InputValue> value);
  // void ZoomOut(SharedPtr<InputValue> value);

  void SelectEntity(SharedPtr<InputValue> value);

  void MoveEntity(SharedPtr<InputValue> value);

  void ToggleLightning(SharedPtr<InputValue> value);

  void ToggleColliders(SharedPtr<InputValue> value);

  EditorCameraEntity* m_editorCamera = nullptr;
  SharedPtr<InputMapping> m_editorBindings;
  Vector2f m_direction;
  Vector<Entity*> m_selectedEntities;
};

// REGISTER_CLASS(EditorControllerEntity)
