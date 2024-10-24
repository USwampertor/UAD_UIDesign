#include "uiEditorCamera.h"
#include "uiCamera.h"
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
  SetPosition(Vector2f(0, 0));
}

void EditorCameraEntity::SetToAvailableArea()
{
  ImVec2 availableArea = ImGui::GetIO().DisplaySize;
  uint32 id = ImGui::GetID("MainDock##2");
  ImGuiDockNode* mainNode = ImGui::DockBuilderGetCentralNode(id);
  if (mainNode == nullptr) { return; }
  // ImGui::DockBuilderGetCentralNode(id);
  // Retrieve the top-left position and size of the node
  ImVec2 topLeft = mainNode->Pos;                // Top-left corner
  ImVec2 size = mainNode->Size;                  // Width and height of the node
  ImVec2 bottomRight = ImVec2(topLeft.x + size.x, topLeft.y + size.y);  // Bottom-right corner

  // Calculate the four corners
  ImVec2 topRight = ImVec2(topLeft.x + size.x, topLeft.y);
  ImVec2 bottomLeft = ImVec2(topLeft.x, topLeft.y + size.y);
  // m_camera->setViewport();
  m_camera->setViewport(FloatRect(topLeft.x / availableArea.x,
                                  topLeft.y / availableArea.y,
                                  size.x / availableArea.x,
                                  size.y / availableArea.y));
}

void EditorCameraEntity::Update(const float& deltaMS)
{
  Entity::Update(deltaMS);
  // SetToAvailableArea();
}