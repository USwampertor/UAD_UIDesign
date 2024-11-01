#include "uiEditor.h"

void Editor::Initialize()
{
  m_editorColor = { 100, 100, 100 };
  m_builder.Initialize();
  m_camera.Initialize();
  m_controller.Initialize();
  m_controller.m_editorCamera = &m_camera;
}

void Editor::Update(const float& deltaMS)
{
  m_controller.Update(deltaMS);
  m_camera.Update(deltaMS);
}

void Editor::LoadEditorResources()
{

}

void Editor::RenderEditorItems(RenderWindow& w)
{
  // sf::RenderStates state;
  // state.shader = m_camera.m_gridShader;
  // w.draw(*m_camera.m_grid, state);
}
