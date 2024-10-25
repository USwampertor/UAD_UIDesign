#include "uiEditorCamera.h"

#include "uiBoid.h"
#include "uiCamera.h"
#include "uiSceneManager.h"
#include "uiWindowManager.h"

#include "imgui.h"
#include "imgui-SFML.h"
#include "imgui_stdlib.h"
#include "imgui_internal.h"

void EditorCameraEntity::Initialize()
{
  Entity::Initialize();
  Vector2f s(WindowManager::Instance().m_mainWindow.getSize().x, WindowManager::Instance().m_mainWindow.getSize().y);
  m_camera = CreateComponent<Camera>(Vector2f(0, 0), s);
}

void EditorCameraEntity::SetToAvailableArea()
{
  ImVec2 availableArea = ImGui::GetIO().DisplaySize;
  // ImGuiDockNode* centralNode = ImGui::DockBuilderGetNode(ImGui::GetID("MainDock##2"));
  if (m_centralNode == nullptr) { return; }
  ImVec2 centralNodeSize = m_centralNode->CentralNode->Size;
  ImVec2 centralNodeStartPos = m_centralNode->CentralNode->Pos;
  // ImGui::DockBuilderGetCentralNode(id);
  // Retrieve the top-left position and size of the node
  Vector2f position(centralNodeStartPos.x / availableArea.x, 
                    centralNodeStartPos.y / availableArea.y);
  Vector2f size(centralNodeSize.x / availableArea.x, 
                centralNodeSize.y / availableArea.y);
  m_camera->setViewport(FloatRect(position.x, position.y, size.x, size.y));
  m_camera->setSize(Vector2f(centralNodeSize.x * m_cameraActualZoom, 
                             centralNodeSize.y * m_cameraActualZoom));
}

void EditorCameraEntity::Update(const float& deltaMS)
{
  SetToAvailableArea();
  Entity::Update(deltaMS);
}