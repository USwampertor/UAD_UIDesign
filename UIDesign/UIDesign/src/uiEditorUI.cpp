#include "uiEditorUI.h"

#include "uiApp.h"
#include "uiInputManager.h"
#include "uiClassRegisters.h"
#include "uiProjectBuilder.h"
#include "uiResourceManager.h"
#include "uiSceneManager.h"
#include "uiTexture.h"
#include "uiUtilities.h"
#include "uiVector2.h"


#include "imgui.h"
#include "imgui-SFML.h"
#include "imgui_stdlib.h"
#include "ImGuiFileDialog.h"

void EditorUI::Initialize()
{

}

void EditorUI::DrawUI()
{
#if UI_EDITOR_MODE

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
      if (ImGui::BeginMenu("Editor"))
      {
        m_windowVisibilities["ViewportOptions"] = ImGui::MenuItem("Viewport Options", "");
        ImGui::EndMenu();
      }
      // 
      if (ImGui::BeginMenu("Create"))
      {
        if (ImGui::BeginMenu("Entities", ""))
        {
          for (auto it = ClassRegisters::GetEntityRegistry().begin(); it != ClassRegisters::GetEntityRegistry().end(); ++it)
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
        ImGui::SameLine();
        ImGui::InputText("##ProjectName", &App::Instance().m_projectBuilder->m_settings.m_projectName, ImGuiInputTextFlags_AlwaysOverwrite);
        ImGui::Text("Icon:");
        ImGui::SameLine();


        m_windowVisibilities["iconPopup"] = ImGui::ImageButton("IconImage##1",
            *ResourceManager::Instance().GetResource<Texture>(App::Instance().m_projectBuilder->m_projectIconStr).get(),
            Vector2f(32.0f, 32.0f));
      }
      ImGui::Separator();
      ImGui::Text("Cookable Scenes");



      for (int32 i = 0; i < SceneManager::Instance().m_scenes.size(); ++i)
      {
        ImGui::PushID(i);
        SharedPtr<Scene> item = SceneManager::Instance().m_scenes[i];
        ImGui::Text(Utils::Format("%d )", i).c_str());
        ImGui::SameLine();
        if (ImGui::Checkbox(Utils::Format("##CkbxScn_%s", item->m_sceneName.c_str()).c_str(),
                            &m_windowVisibilities[Utils::Format("##CkbxScn_%s", item->m_sceneName.c_str())]))
        {
          App::Instance().m_projectBuilder->m_settings.m_cookableScenes[i] = SceneManager::Instance().FindScene(item->m_sceneName);
        }
        else 
        {
          App::Instance().m_projectBuilder->m_settings.m_cookableScenes[i] = nullptr;
        }
        ImGui::SameLine();
        ImGui::Button(item->m_sceneName.c_str(), ImVec2(ImGui::GetWindowWidth() - ImGui::CalcItemWidth() / 2, ImGui::GetFrameHeight()));

        // Our buttons are both drag sources and drag targets here!
        if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_None))
        {
          // Set payload to carry the index of our item (could be anything)
          ImGui::SetDragDropPayload("PROJECTSCENES", &i, sizeof(int));

          // Display preview (could be anything, e.g. when dragging an image we could decide to display
          // the filename and a small preview of the image, etc.)
          ImGui::Text("Reorder %s", item->m_sceneName.c_str());
          ImGui::EndDragDropSource();
        }
        if (ImGui::BeginDragDropTarget())
        {
          if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("PROJECTSCENES"))
          {
            IM_ASSERT(payload->DataSize == sizeof(int));
            int payload_n = *(const int*)payload->Data;
            
            std::swap(SceneManager::Instance().m_scenes[payload_n], SceneManager::Instance().m_scenes[i]);

          }
          ImGui::EndDragDropTarget();
        }
        ImGui::PopID();

        // ImGui::Selectable(item->m_sceneName.c_str());
        // if (ImGui::IsItemActive() && !ImGui::IsItemHovered())
        // {
        //   int n_next = i + (ImGui::GetMouseDragDelta(0).y < 0.f ? -1 : 1);
        //   if (n_next >= 0 && n_next < SceneManager::Instance().m_scenes.size())
        //   {
        //     std::swap(SceneManager::Instance().m_scenes[n_next], SceneManager::Instance().m_scenes[i]);
        //     ImGui::ResetMouseDragDelta();
        //   }
        // }
      }

      ImGui::Separator();

      ImGui::Separator();


      // Hit that motherfucking button
      if (ImGui::Button("Build Project"))
      {
        IGFD::FileDialogConfig config;
        config.path = ".";
        ImGuiFileDialog::Instance()->OpenDialog("ChooseDirDlgKey", "Choose a Directory", nullptr, config);
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
        ImGui::Text(SceneManager::Instance().m_activeScene->m_sceneName.c_str());
        ImGui::Separator();
      }
      ImGui::End();
    }

    if (m_windowVisibilities["ViewportOptions"])
    {
      ImGui::OpenPopup("popup_viewport");
      m_windowVisibilities["ViewportOptions"] = false;
    }
    if (ImGui::BeginPopup("popup_viewport"))
    {
      ImGui::Text("Viewport options");
      if (ImGui::Button("Close"))
      {
        ImGui::CloseCurrentPopup();
      }
      ImGui::EndPopup();
    }

    if (ImGuiFileDialog::Instance()->Display("ChooseDirDlgKey")) {
      if (ImGuiFileDialog::Instance()->IsOk()) { // action if OK
        std::string filePathName = ImGuiFileDialog::Instance()->GetFilePathName();
        std::string filePath = ImGuiFileDialog::Instance()->GetCurrentPath();
        App::Instance().m_projectBuilder->m_settings.m_projectDir = filePath;
        // action
        if (App::Instance().m_projectBuilder->m_settings.m_projectName.empty())
        {
          App::Instance().m_projectBuilder->m_settings.m_projectName = "UIGame";
        }
        App::Instance().m_projectBuilder->BuildProject();
      }

      // close
      ImGuiFileDialog::Instance()->Close();
    }


    if (m_windowVisibilities["iconPopup"])
    {
      ImGui::OpenPopup("icon_options");
      m_windowVisibilities["iconPopup"] = false;
    }
    if (ImGui::BeginPopup("icon_options"))
    {
      ImGui::Text("Set Image");
      ImGui::Separator();


      

      Map<SizeT, SharedPtr<Resource>>::iterator res;
      for (res = ResourceManager::Instance().m_resources.begin(); 
           res != ResourceManager::Instance().m_resources.end(); 
           ++res)
      {
        if (res->second->GetType() == eRESOURCETYPE::TEXTURE)
        {
          if (ImGui::Selectable(res->second->m_resName.c_str()))
          {
            App::Instance().m_projectBuilder->m_projectIconStr = res->second->m_resName;
          }
        }
        // if (ResourceManager::Instance().GetResource<Texture>(res->second->m_resName) != nullptr)
        // {
        //   if (ImGui::Selectable(res->second->m_resName.c_str()))
        //   {
        //     App::Instance().m_projectBuilder->m_projectIconStr = res->second->m_resName;
        //   }
        // }
      }

      ImGui::EndPopup();
    }

    /************************************************************************/
    /*                                                                      */
    /************************************************************************/

    ImGui::SetNextWindowSize(ImVec2(300, 150));
    ImGui::SetNextWindowPos(ImVec2(ImGui::GetIO().DisplaySize.x / 2, ImGui::GetIO().DisplaySize.y / 2) );


  }


  ImGui::End();


#endif
}
