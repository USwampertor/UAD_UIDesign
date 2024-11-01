#include "uiEditorController.h"

#include "uiCamera.h"
#include "uiCameraFollower.h"
#include "uiEditorCamera.h"
#include "uiInputManager.h"
#include "uiLogger.h"
#include "uiSceneManager.h"
#include "uiUtilities.h"
#include "uiVector2.h"
#include "uiWindowManager.h"

#include "imgui.h"

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
  if ((value->GetState() == Input::eINPUTSTATE::PRESSED ||
      value->GetState() == Input::eINPUTSTATE::HELD) && 
      !ImGui::GetIO().WantCaptureMouse)
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
  if ((value->GetState() == Input::eINPUTSTATE::PRESSED ||
      value->GetState() == Input::eINPUTSTATE::HELD) && 
      !ImGui::GetIO().WantCaptureMouse)
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
  if ((value->GetState() == Input::eINPUTSTATE::PRESSED ||
      value->GetState() == Input::eINPUTSTATE::HELD) && 
      !ImGui::GetIO().WantCaptureMouse)
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
  if ((value->GetState() == Input::eINPUTSTATE::PRESSED ||
      value->GetState() == Input::eINPUTSTATE::HELD) && 
      !ImGui::GetIO().WantCaptureMouse)
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
  if (!ImGui::GetIO().WantCaptureMouse)
  {
    m_editorCamera->m_cameraActualZoom += 0.1f * -(value->m_value);
    m_editorCamera->m_cameraActualZoom = std::clamp(m_editorCamera->m_cameraActualZoom, 0.1f, 1000.0f);
  }

}

void EditorControllerEntity::SelectEntity(SharedPtr<InputValue> value)
{
  if (value->GetState() == Input::eINPUTSTATE::PRESSED && !ImGui::GetIO().WantCaptureMouse)
  {
    m_selectedEntities.clear();
    for (const auto& e : SceneManager::Instance().m_activeScene->m_entities)
    {
      Vector2f entityPos(e->GetTransform().position.x, e->GetTransform().position.y);
      Vector2i mouseWndPos = Input::Mouse::getPosition(WindowManager::Instance().m_mainWindow);
      Vector2f mousePos = WindowManager::Instance().m_mainWindow.mapPixelToCoords(mouseWndPos);
      float d = Vec2::Length(entityPos - mousePos);
      Logger::Instance().ToConsole(Utils::Format("%f", d));
      if (d < 100.0f)
      {
        m_selectedEntities.push_back(e.get());
        break;
      }
    }
  }
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

