#include "uiUI.h"

#include "uiInputManager.h"

#include "Remotery.h"

void UI::Initialize(RenderWindow& window)
{
  ImGui::SFML::Init(window);
}

void UI::ProcessEvent(const RenderWindow& window, const HEvent& event)
{
  ImGui::SFML::ProcessEvent(window, event);
}

void UI::Update( RenderWindow& window,  Time& dt)
{
  ImGui::SFML::Update(window, dt);
}

void UI::RenderUI()
{
  rmt_ScopedCPUSample(RenderUI, 0);
  ImGui::Begin("Inputs");
  ImGui::Text(InputManager::Instance().m_values[Input::eINPUTCODE::KeyCodeW][0]->GetState()._to_string());
  ImGui::Text(InputManager::Instance().m_values[Input::eINPUTCODE::KeyCodeA][0]->GetState()._to_string());
  ImGui::Text(InputManager::Instance().m_values[Input::eINPUTCODE::KeyCodeS][0]->GetState()._to_string());
  ImGui::Text(InputManager::Instance().m_values[Input::eINPUTCODE::KeyCodeD][0]->GetState()._to_string());
  ImGui::Text(InputManager::Instance().m_values[Input::eINPUTCODE::KeyCodeEnter][0]->GetState()._to_string());
  if (ImGui::Button("My new Button"))
  {
    ImGui::Text("Pressed");
  }
  ImGui::End();
}

void UI::Render(RenderWindow& window)
{
  rmt_ScopedCPUSample(Render, 0);
  ImGui::SFML::Render(window);
}

void UI::Finish()
{
  ImGui::SFML::Shutdown();
}