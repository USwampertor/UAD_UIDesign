#include "uiEditorUI.h"
#include "uiInputManager.h"
#include "uiClassRegisters.h"
#include "uiProjectBuilder.h"
#include "uiResourceManager.h"
#include "uiSceneManager.h"
#include "uiTexture.h"
#include "uiVector2.h"


#include "imgui.h"
#include "imgui-SFML.h"
#include "imgui_stdlib.h"

void EditorUI::Initialize()
{
  m_windowVisibilities["Logger"] = true;
  m_windowVisibilities["EntityInspector"] = true;
}

void EditorUI::DrawUI()
{
  ImGui::SetNextWindowPos(ImVec2(0, 0));
  ImGui::SetNextWindowSize(ImVec2(ImGui::GetIO().DisplaySize.x, ImGui::GetIO().DisplaySize.y));
  ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
  ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
  ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
  if (ImGui::Begin("MainDock##1",
                    nullptr,
                    ImGuiWindowFlags_NoTitleBar |
                    ImGuiWindowFlags_MenuBar |
                    ImGuiWindowFlags_NoMove |
                    ImGuiWindowFlags_NoDocking |
                    ImGuiWindowFlags_NoScrollbar |
                    ImGuiWindowFlags_NoCollapse |
                    ImGuiWindowFlags_NoBackground |
                    ImGuiWindowFlags_NoResize |
                    ImGuiWindowFlags_NoBringToFrontOnFocus |
                    ImGuiWindowFlags_NoNavFocus ))
  {
    ImGui::PopStyleVar(3);
    if (ImGui::BeginMainMenuBar())
    {
      if (ImGui::BeginMenu("File"))
      {
        ImGui::MenuItem("New", "CTRL+N");
        ImGui::MenuItem("Save", "CTRL+S");
        ImGui::MenuItem("Save as", "CTRL+SHIFT+S");
        ImGui::MenuItem("Preferences", "");
        ImGui::MenuItem("Project Settings", "CTRL+SHIFT+P", &m_windowVisibilities["ProjectSettings"]);
        ImGui::EndMenu();
      }
      // 
      if (ImGui::BeginMenu("View"))
      {
        ImGui::MenuItem("Logger", "", &m_windowVisibilities["Logger"]);
        ImGui::MenuItem("Scene Graph", "", &m_windowVisibilities["SceneGraph"]);
        ImGui::MenuItem("Entity Inspector", "", &m_windowVisibilities["EntityInspector"]);
        ImGui::MenuItem("Resource Explorer", "", &m_windowVisibilities["Resources"]);
        ImGui::EndMenu();
      }
      // 
      if (ImGui::BeginMenu("Create"))
      {
        if (ImGui::BeginMenu("Entities", ""))
        {
          for (auto it = ClassRegisters::GetRegistry().begin(); it != ClassRegisters::GetRegistry().end(); ++it)
          {
            ImGui::MenuItem(it->first.c_str());
          }
          ImGui::EndMenu();
        }
        ImGui::EndMenu();
      }
    }
    ImGui::EndMainMenuBar();

    ImGuiID dockSpaceID = ImGui::GetID("MainDock##2");
    ImGui::DockSpace(dockSpaceID, ImVec2(0, 0), ImGuiDockNodeFlags_PassthruCentralNode | ImGuiDockNodeFlags_NoDockingOverCentralNode);

    /************************************************************************/
    /*                                                                      */
    /************************************************************************/
    if (m_windowVisibilities["ProjectSettings"])
    {
      if (ImGui::Begin("Project Settings"))
      {
        ImGui::Text("Project Settings");
        ImGui::Text("Name");
        ImGui::InputText("##ProjectName", &ProjectBuilder::Instance().m_settings.m_projectName, ImGuiInputTextFlags_AlwaysOverwrite);
        ImGui::Text("Icon:");
        ImGui::SameLine();
        ImGui::ImageButton("IconImage##1", 
          *ResourceManager::Instance().GetResource<Texture>("idleBullet_0").get(),
          Vector2f(32.0f, 32.0f));
      }
      ImGui::End();
    }

    if (m_windowVisibilities["EntityInspector"])
    {
      if (ImGui::Begin("Entity Inspector"))
      {

      }
      ImGui::End();
    }

    if (m_windowVisibilities["Logger"])
    {
      if (ImGui::Begin("Logger"))
      {
        
      }
      ImGui::End();
    }

    if (m_windowVisibilities["Resources"])
    {
      if (ImGui::Begin("Resource Explorer"))
      {
        ImGui::Columns(2, "ResourcesColums");
        ImGui::BeginChild("Explorer", ImVec2(0, 0));
        ImGui::Text("Explorer");
        ImGui::EndChild();
        ImGui::NextColumn();
        ImGui::BeginChild("Items", ImVec2(0, 0));
        ImGui::Text("Items");
        ImGui::EndChild();
        ImGui::Columns(1);
      }
      ImGui::End();
    }

    if (m_windowVisibilities["SceneGraph"])
    {
      if (ImGui::Begin("Scene Graph"))
      {
        
      }
      ImGui::End();
    }

    /************************************************************************/
    /*                                                                      */
    /************************************************************************/

  }
  ImGui::End();

}
