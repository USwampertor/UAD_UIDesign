#pragma once
#include "uiPrerequisites.h"

#include "uiEditorCamera.h"
#include "uiCameraFollower.h"
#include "uiColor.h"
#include "uiEditorController.h"
#include "uiProjectBuilder.h"
#include "uiWindow.h"

class Editor
{
public:
  void Initialize();

  void Update(const float& deltaMS);

  void LoadEditorResources();

  void RenderEditorItems(RenderWindow& w);

  ProjectBuilder m_builder;
  EditorCameraEntity m_camera;
  EditorControllerEntity m_controller;
  Color m_editorColor;
};

