#include "uiEditorUI.h"

#include "uiApp.h"
#include "uiAnimator.h"
#include "uiInputManager.h"
#include "uiClassRegisters.h"
#include "uiLogger.h"
#include "uiResourceManager.h"
#include "uiSceneManager.h"
#include "uiTexture.h"
#include "uiUtilities.h"
#include "uiVector2.h"


#ifndef IMGUI_DEFINE_MATH_OPERATORS
#define IMGUI_DEFINE_MATH_OPERATORS
#endif
#include "imgui.h"
#include "imgui-SFML.h"
#include "imgui_stdlib.h"
#include "ImGuiFileDialog.h"
#include "imspinner.h"

void EditorUI::Initialize()
{
  Logger::Instance().AddOnLogAddedCallback(std::bind(&EditorUI::AddDebuggerLog, this, std::placeholders::_1));
}

void EditorUI::AddDebuggerLog(const Log& newLog)
{
  if (newLog.m_flag == eLOGFLAG::DEBUGGER)
  {
    m_debugLogs.push_back(&newLog);
  }
}

void EditorUI::DrawUI()
{
  if (App::Instance().m_parser.HasFlag("editor"))
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
      ImGuiWindowFlags_NoNavFocus))
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
          ImGui::MenuItem("Project Settings",
            "CTRL+SHIFT+P",
            &m_windowVisibilities["ProjectSettings"]);
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
            for (auto it = ClassRegisters::GetEntityRegistry().begin();
              it != ClassRegisters::GetEntityRegistry().end();
              ++it)
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

      ImGui::DockSpace(dockSpaceID,
        ImVec2(0, 0),
        ImGuiDockNodeFlags_PassthruCentralNode |
        ImGuiDockNodeFlags_NoDockingOverCentralNode);

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
          ImGui::InputText("##ProjectName",
            &App::Instance().m_editor->m_builder.m_settings.m_projectName,
            ImGuiInputTextFlags_AlwaysOverwrite);
          ImGui::Text("Icon:");
          ImGui::SameLine();


          m_windowVisibilities["iconPopup"] = ImGui::ImageButton("IconImage##1",
            *ResourceManager::Instance().GetResource<Texture>(App::Instance().m_editor->m_builder.m_projectIconStr).get(),
            Vector2f(32.0f, 32.0f));
        }
        ImGui::Separator();

        ImGui::Text("Video Resolutions");

        for (int32 i = 0; i < App::Instance().m_editor->m_builder.m_settings.m_resolutions.size(); ++i)
        {
          String x = Utils::Format("%d",
            App::Instance().m_editor->m_builder.m_settings.m_resolutions[i]->width);
          String y = Utils::Format("%d",
            App::Instance().m_editor->m_builder.m_settings.m_resolutions[i]->height);
          ImGui::PushItemWidth(ImGui::GetWindowSize().x / 3);
          // ImGui::SetNextWindowContentSize(ImVec2(ImGui::GetWindowSize().x / 8, ImGui::CalcItemWidth()));
          ImGui::InputText(Utils::Format("##VideoResolution_%d_x", i).c_str(), &x[0], ImGuiInputTextFlags_CharsDecimal |
            ImGuiInputTextFlags_CharsNoBlank |
            ImGuiInputTextFlags_AlwaysOverwrite);
          // bool xisValid = !x.empty() && std::find_if(x.begin(), x.end(), [](unsigned char c) { return !std::isdigit(c); }) == x.end();
          x = Utils::IsStringNumber(x) ? x : "0";
          ImGui::SameLine();
          // ImGui::SetNextWindowContentSize(ImVec2(ImGui::GetWindowSize().x / 4, ImGui::CalcItemWidth()));
          ImGui::InputText(Utils::Format("##VideoResolution_%d_y", i).c_str(), &y[0], ImGuiInputTextFlags_CharsDecimal |
            ImGuiInputTextFlags_CharsNoBlank |
            ImGuiInputTextFlags_AlwaysOverwrite);
          // bool yisValid = !y.empty() && std::find_if(y.begin(), y.end(), [](unsigned char c) { return !std::isdigit(c); }) == y.end();
          y = Utils::IsStringNumber(y) ? y : "0";
          ImGui::PopItemWidth();

          App::Instance().m_editor->m_builder.m_settings.m_resolutions[i]->width = std::stoi(x);
          App::Instance().m_editor->m_builder.m_settings.m_resolutions[i]->height = std::stoi(y);
          ImGui::SameLine();

          if (ImGui::Button("x"))
          {
            App::Instance().m_editor->m_builder.m_settings.m_resolutions.erase(App::Instance().m_editor->m_builder.m_settings.m_resolutions.begin() + i);
            break;
          }
        }

        if (ImGui::Button("+"))
        {
          App::Instance().m_editor->m_builder.m_settings.m_resolutions.push_back(new VideoMode(0, 0));
        }

        ImGui::Separator();

        ImGui::Checkbox("Use vertical sync", &App::Instance().m_editor->m_builder.m_settings.m_shouldUseVerticalSync);

        String framerate = Utils::Format("%d", App::Instance().m_editor->m_builder.m_settings.m_framerate);
        ImGui::InputText("Framerate", &framerate[0], ImGuiInputTextFlags_CharsDecimal |
          ImGuiInputTextFlags_CharsNoBlank |
          ImGuiInputTextFlags_AlwaysOverwrite);
        framerate = Utils::IsStringNumber(framerate) ? framerate : "60";
        App::Instance().m_editor->m_builder.m_settings.m_framerate = std::stoi(framerate);
        ImGui::Separator();
        ImGui::Text("Cookable Scenes");



        for (int32 i = 0; i < SceneManager::Instance().m_scenes.size(); ++i)
        {
          ImGui::PushID(i);
          SharedPtr<Scene> item = SceneManager::Instance().m_scenes[i];
          ImGui::Text(Utils::Format("%d )", i).c_str());
          ImGui::SameLine();
          ImGui::Checkbox(Utils::Format("##CkbxScn_%s",
            item->m_sceneName.c_str()).c_str(),
            &m_windowVisibilities[Utils::Format("##CkbxScn_%s",
              item->m_sceneName.c_str())]);

          if (m_windowVisibilities[Utils::Format("##CkbxScn_%s", item->m_sceneName.c_str())])
          {
            Scene* toCook = SceneManager::Instance().FindScene(item->m_sceneName);
            App::Instance().m_editor->m_builder.m_settings.m_cookableScenes[i] = toCook;
          }
          else
          {
            App::Instance().m_editor->m_builder.m_settings.m_cookableScenes[i] = nullptr;
          }
          ImGui::SameLine();
          ImGui::Button(item->m_sceneName.c_str(),
            ImVec2(ImGui::GetWindowWidth() - ImGui::CalcItemWidth() / 2,
              ImGui::GetFrameHeight()));

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
          for (auto& e : App::Instance().m_editor->m_controller.m_selectedEntities)
          {
            String n = e->GetName();
            ImGui::Text("EntityName");
            ImGui::SameLine();
            if (ImGui::InputText("##entityName", &n[0], ImGuiInputTextFlags_EnterReturnsTrue))
            {
              e->SetName(n);
            }
            ImGui::Text("Transform");
            ImGui::Separator();
            ImGui::Text("Position");
            Vector2f pos = e->GetTransform().position;
            ImGui::Text("X: ");
            ImGui::SameLine();
            ImGui::PushItemWidth(ImGui::GetWindowSize().x / 4);
            ImGui::DragFloat("##entityX", &pos.x, 0.05f, -1000000.0f, +1000000.0f, "%.3f");
            ImGui::PopItemWidth();
            ImGui::SameLine();
            ImGui::Text("Y: ");
            ImGui::SameLine();
            ImGui::PushItemWidth(ImGui::GetWindowSize().x / 4);
            ImGui::DragFloat("##entityY", &pos.y, 0.05f, -1000000.0f, +1000000.0f, "%.3f");
            ImGui::PopItemWidth();
            e->SetPosition(pos);

            // Components
            if (e->GetComponent<Animator>() != nullptr)
            {
              ImGui::Separator();
              ImGui::Text("Animator");
              for (auto& animation : e->GetComponent<Animator>()->m_animations)
              {
                ImGui::Text(animation.first.c_str());
              }
            }
            if (e->GetComponent<Sprite>() != nullptr)
            {
              ImGui::Separator();
              ImGui::Text("Sprite");
              ImGui::ImageButton("##entitySprite", 
                                 static_cast<sf::Sprite>(*e->GetComponent<Sprite>()), 
                                 Vector2f(ImGui::GetWindowSize().x / 2, 
                                          ImGui::GetWindowSize().x / 2));
            }
            // End Components
          }
        }
        ImGui::End();
      }

      if (m_windowVisibilities["Logger"])
      {
        if (ImGui::Begin("Logger"))
        {
          if (ImGui::Button("Clear"))
          {
            m_debugLogs.clear();
          }
          ImGui::SameLine();
          // TODO: Make Collapse be able to see the full log
          // TODO: Make Collapse also make a shorter version of the log
          ImGui::Button("Collapse");
          ImGui::SameLine();
          // TODO:: Add a Pause System
          ImGui::Button("ErrorPause");
          ImGui::SameLine();
          ImGui::Checkbox("Error", &m_windowVisibilities["errorCheckbox"]);
          ImGui::SameLine();
          ImGui::Checkbox("Warnings", &m_windowVisibilities["warningCheckbox"]);
          ImGui::SameLine();
          ImGui::Checkbox("Logs", &m_windowVisibilities["logCheckbox"]);
          ImGui::Spacing();
          ImGui::Separator();
          ImGui::Spacing();

          ImGui::BeginChild("LogsArea", ImVec2(0, 0), true, ImGuiWindowFlags_HorizontalScrollbar);
          for (const auto& log : m_debugLogs)
          {
            if (m_windowVisibilities["errorCheckbox"] && 
                log->m_warningLevel == eLOGLEVEL::ERROR)
            {
              ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(255, 0, 0, 255));
              if (ImGui::Selectable(log->m_message.c_str(), &m_windowVisibilities["selectedLog"]))
              {
                // TODO: Add an extra string that you can see with more precision
              }
              ImGui::PopStyleColor();
            }
            else if (m_windowVisibilities["warningCheckbox"] && 
                     log->m_warningLevel == eLOGLEVEL::WARNING)
            {
              ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(255, 200, 0, 255));
              if (ImGui::Selectable(log->m_message.c_str(), &m_windowVisibilities["selectedLog"]))
              {
                // TODO: Add an extra string that you can see with more precision
              }
              ImGui::PopStyleColor();
            }
            else if (m_windowVisibilities["logCheckbox"] && 
                     log->m_warningLevel == eLOGLEVEL::DEFAULT)
            {
              if (ImGui::Selectable(log->m_message.c_str(), &m_windowVisibilities["selectedLog"]))
              {
                // TODO: Add an extra string that you can see with more precision
              }
            }
          }
          ImGui::EndChild();

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
          App::Instance().m_editor->m_builder.m_settings.m_projectDir = filePath;
          // action
          if (App::Instance().m_editor->m_builder.m_settings.m_projectName.empty())
          {
            App::Instance().m_editor->m_builder.m_settings.m_projectName = "UIGame";
          }
          m_windowVisibilities["buildingPopup"] = true;
          App::Instance().m_editor->m_builder.StartBuildingThread();
        }

        // close
        ImGuiFileDialog::Instance()->Close();
      }

      if (m_windowVisibilities["buildingPopup"])
      {
        ImVec2 pos = ImGui::GetIO().DisplaySize;
        ImVec2 nextSize(pos.x / 7, pos.y / 7);
        pos.x = pos.x / 2 - nextSize.x / 2;
        pos.y = pos.y / 2 - nextSize.y / 2;
        ImGui::SetNextWindowPos(pos);
        ImGui::SetNextWindowSize(nextSize);
        ImGui::OpenPopup("building_popup");
      }
      if (ImGui::BeginPopup("building_popup"))
      {
        ImGui::Text("Building...");
        ImGui::Separator();
        if (App::Instance().m_editor->m_builder.m_buildingPercentage < 100)
        {
          ImSpinner::SpinnerFadeDots("Building",
            ImSpinner::Radius(16),
            ImSpinner::Thickness(6),
            ImSpinner::Color(ImColor(255, 255, 255, 255)),
            ImSpinner::Speed(10));
          ImGui::Text(Utils::Format("%2f",
            App::Instance().m_editor->m_builder.m_buildingPercentage).c_str());
          ImGui::Separator();
        }
        else if (App::Instance().m_editor->m_builder.m_buildingPercentage == 100)
        {
          if (ImGui::Button("Build Completed"))
          {
            m_windowVisibilities["buildingPopup"] = false;
            ImGui::CloseCurrentPopup();
          }
        }
        // App::Instance().m_projectBuilder->BuildProject();
        ImGui::EndPopup();
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
              App::Instance().m_editor->m_builder.m_projectIconStr = res->second->m_resName;
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



      ImGuiDockNode* centralNode = ImGui::DockBuilderGetNode(ImGui::GetID("MainDock##2"));
      App::Instance().m_editor->m_camera.m_centralNode = centralNode;
      ImVec2 centralNodeSize = centralNode->CentralNode->Size;
      ImVec2 centralNodeStartPos = centralNode->CentralNode->Pos;
      float menuBarSize = ImGui::GetFrameHeight();  // Get height of menu bar
      ImGui::SetNextWindowPos(ImVec2(centralNodeStartPos.x, menuBarSize));

      // Set the bar to be the full width of the window, but with a small fixed height
      ImGui::SetNextWindowSize(ImVec2(centralNodeSize.x, menuBarSize));

      ImGui::Begin("##CameraInformation",
        nullptr,
        ImGuiWindowFlags_NoTitleBar |
        ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_NoScrollbar |
        ImGuiWindowFlags_NoDocking);

      ImGui::Text("Camera Position");
      ImGui::SameLine();
      ImGui::Text(Utils::Format("X: %f --- Y: %f",
        App::Instance().m_editor->m_camera.GetTransform().position.x,
        App::Instance().m_editor->m_camera.GetTransform().position.y).c_str());

      ImGui::End();

      /************************************************************************/
      /*                                                                      */
      /************************************************************************/
      // Wtf was this supposed to do?
      // ImGui::SetNextWindowSize(ImVec2(300, 150));
      // ImGui::SetNextWindowPos(ImVec2(ImGui::GetIO().DisplaySize.x / 2, ImGui::GetIO().DisplaySize.y / 2) );


    }


    ImGui::End();


  }
}
