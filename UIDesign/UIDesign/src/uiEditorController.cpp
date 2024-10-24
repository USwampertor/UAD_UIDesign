#include "uiEditorController.h"
#include "uiInputManager.h"


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
}

void EditorControllerEntity::Update(const float& deltaMS)
{
  Entity::Update(deltaMS);
}

void EditorControllerEntity::MoveCameraUp(SharedPtr<InputValue> value)
{

}

void EditorControllerEntity::MoveCameraDown(SharedPtr<InputValue> value)
{

}

void EditorControllerEntity::MoveCameraLeft(SharedPtr<InputValue> value)
{

}

void EditorControllerEntity::MoveCameraRight(SharedPtr<InputValue> value)
{

}

void EditorControllerEntity::Zoom(SharedPtr<InputValue> value)
{

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

