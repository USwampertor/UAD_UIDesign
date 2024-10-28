#include "uiUI.h"

#include "uiApp.h"

#include "imgui.h"
#include "imgui-SFML.h"
#include "Remotery.h"


void UI::Initialize(RenderWindow& window)
{
  window.requestFocus();
  ImGui::SFML::Init(window);
  m_editorUI.Initialize();
}

void UI::ProcessEvent(const RenderWindow& window, const HEvent& event)
{
  ImGui::SFML::ProcessEvent(window, event);
}

void UI::Update( RenderWindow& window, Time& dt)
{
  ImGui::SFML::Update(window, dt);
}

void UI::GenerateIMGUI()
{
  // rmt_ScopedCPUSample(GenerateIMGUI, 0);

  if (App::Instance().m_parser.HasFlag("editor"))
  {
    m_editorUI.DrawUI();
    // ImGui::ShowDemoWindow();
  }
}

void UI::Render(RenderWindow& window)
{
  // rmt_ScopedCPUSample(Render, 0);
  ImGui::SFML::Render(window);
}

void UI::Finish()
{
  ImGui::SFML::Shutdown();
}