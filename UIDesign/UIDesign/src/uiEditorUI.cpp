#include "uiEditorUI.h"
#include "uiInputManager.h"
#include "uiClassRegisters.h"
#include "uiSceneManager.h"

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
      // if (ImGui::BeginMenu("View"))
      // {
      //   ImGui::MenuItem("Logger", "", &m_windowVisibilities["Logger"]);
      //   ImGui::MenuItem("Scene Graph", "", &m_windowVisibilities["SceneGraph"]);
      //   ImGui::MenuItem("Entity Inspector", "", &m_windowVisibilities["EntityInspector"]);
      // }
      // ImGui::EndMenu();
      // 
      // if (ImGui::BeginMenu("Create"))
      // {
      //   if (ImGui::BeginMenu("Entities", ""))
      //   {
      //     for (auto it = ClassRegisters::GetRegistry().begin(); it != ClassRegisters::GetRegistry().end(); ++it)
      //     {
      //       ImGui::MenuItem(it->first.c_str());
      //     }
      //   }
      //   ImGui::EndMenu();
      // }
      // ImGui::EndMenu();
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
      }
      ImGui::End();
    }

    if (m_windowVisibilities["EntityInspector"])
    {
      if (ImGui::Begin("Entity Inspector"))
      {
        // ImGui::Text("Properties");
      }
      ImGui::End();
    }

    if (m_windowVisibilities["Logger"])
    {
      if (ImGui::Begin("Logger"))
      {
//         if (ImGui::BeginTabBar("Logs"))
//         {
//           if (ImGui::BeginTabItem("Debug"))
//           {
//             ImGui::Button("ClearLogs");
//           }
//           ImGui::EndTabItem();
//           if (ImGui::BeginTabItem("Release"))
//           {
//             ImGui::Button("ClearLogs");
//           }
//           ImGui::EndTabItem();
// 
// 
//           ImGui::EndTabBar();
//         }
      }
      ImGui::End();
    }


    if (m_windowVisibilities["SceneGraph"])
    {
      if (ImGui::Begin("Scene Graph"))
      {
        
        ImGui::End();
      }
    }

    /************************************************************************/
    /*                                                                      */
    /************************************************************************/

  }
  ImGui::End();

}
