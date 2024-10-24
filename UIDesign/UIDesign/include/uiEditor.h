#pragma once
#include "uiPrerequisites.h"

#include "uiEditorCamera.h"
#include "uiEditorController.h"
#include "uiProjectBuilder.h"
#include "uiColor.h"

class Editor
{
public:
  void Initialize();

  void Update(const float& deltaMS);

  ProjectBuilder m_builder;
  EditorCameraEntity m_camera;
  EditorControllerEntity m_controller;
  Color m_editorColor;
};

