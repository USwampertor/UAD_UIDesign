#include "uiEditorController.h"
#include "uiInputManager.h"

#include "uiEditorCamera.h"
#include "uiCameraFollower.h"
#include "uiCamera.h"

void EditorControllerEntity::Initialize()
{
  Entity::Initialize();

  m_editorBindings = MakeSharedObject<InputMapping>();
  m_editorBindings->BindAction(Input::eINPUTCODE::KeyCodeW,
                                std::bind(&EditorControllerEntity::MoveCameraUp, 
                                          this,
                                          std::placeholders::_1));
  m_editorBindings->BindAction(Input::eINPUTCODE::KeyCodeA,
                                std::bind(&EditorControllerEntity::MoveCameraLeft, 
                                          this,
                                          std::placeholders::_1));
  m_editorBindings->BindAction(Input::eINPUTCODE::KeyCodeS,
                                std::bind(&EditorControllerEntity::MoveCameraDown, 
                                          this,
                                          std::placeholders::_1));
  m_editorBindings->BindAction(Input::eINPUTCODE::KeyCodeD,
                                std::bind(&EditorControllerEntity::MoveCameraRight, 
                                          this,
                                          std::placeholders::_1));

  m_editorBindings->BindAction(Input::eINPUTCODE::MouseWheelVertical,
                                std::bind(&EditorControllerEntity::Zoom, 
                                          this,
                                          std::placeholders::_1));
  m_editorBindings->BindAction(Input::eINPUTCODE::MouseLeft,
                                std::bind(&EditorControllerEntity::SelectEntity, 
                                          this,
                                          std::placeholders::_1));
  m_editorBindings->BindAction(Input::eINPUTCODE::MouseLeft,
                                std::bind(&EditorControllerEntity::MoveEntity, 
                                          this,
                                          std::placeholders::_1));

  m_editorBindings->BindAction(Input::eINPUTCODE::KeyCodeC,
                                std::bind(&EditorControllerEntity::ToggleColliders, 
                                          this,
                                          std::placeholders::_1));
  m_editorBindings->BindAction(Input::eINPUTCODE::KeyCodeL,
                                std::bind(&EditorControllerEntity::ToggleLightning, 
                                          this,
                                          std::placeholders::_1));
  m_editorBindings->m_enabled = true;

  InputManager::Instance().RegisterInputMapping(m_editorBindings);
}

void EditorControllerEntity::Update(const float& deltaMS)
{
  Entity::Update(deltaMS);
  m_editorCamera->Move(m_direction * (deltaMS * 0.01f) * m_editorCamera->m_cameraMoveSpeed);
  // Move(m_direction * delta * m_speed * 0.01f);
}

void EditorControllerEntity::MoveCameraUp(SharedPtr<InputValue> value)
{
  if (value->GetState() == Input::eINPUTSTATE::PRESSED ||
    value->GetState() == Input::eINPUTSTATE::HELD)
  {
    m_direction.y = -1;
  }
  else if (value->GetState() == Input::eINPUTSTATE::RELEASED)
  {
    m_direction.y = 0;
  }
}

void EditorControllerEntity::MoveCameraDown(SharedPtr<InputValue> value)
{
  if (value->GetState() == Input::eINPUTSTATE::PRESSED ||
    value->GetState() == Input::eINPUTSTATE::HELD)
  {
    m_direction.y = 1;
  }
  else if (value->GetState() == Input::eINPUTSTATE::RELEASED)
    // else
  {
    m_direction.y = 0;
  }
}

void EditorControllerEntity::MoveCameraLeft(SharedPtr<InputValue> value)
{
  if (value->GetState() == Input::eINPUTSTATE::PRESSED ||
    value->GetState() == Input::eINPUTSTATE::HELD)
  {
    m_direction.x = -1;
  }
  else if (value->GetState() == Input::eINPUTSTATE::RELEASED)
  {
    m_direction.x = 0;
  }
}

void EditorControllerEntity::MoveCameraRight(SharedPtr<InputValue> value)
{
  if (value->GetState() == Input::eINPUTSTATE::PRESSED ||
    value->GetState() == Input::eINPUTSTATE::HELD)
  {
    m_direction.x = 1;
  }
  else if (value->GetState() == Input::eINPUTSTATE::RELEASED)
  {
    m_direction.x = 0;
  }
}

void EditorControllerEntity::Zoom(SharedPtr<InputValue> value)
{
  m_editorCamera->m_camera->zoom(m_editorCamera->m_cameraZoomSpeed * value->m_value * 0.001f);
}

void EditorControllerEntity::SelectEntity(SharedPtr<InputValue> value)
{

}

void EditorControllerEntity::MoveEntity(SharedPtr<InputValue> value)
{

}

void EditorControllerEntity::ToggleLightning(SharedPtr<InputValue> value)
{

}

void EditorControllerEntity::ToggleColliders(SharedPtr<InputValue> value)
{

}

