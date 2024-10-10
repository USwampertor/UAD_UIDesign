#pragma once
#include "uiPrerequisites.h"
#include "uiController.h"
#include "uiInputMapping.h"

class Camera;

class EditorControllerEntity : public ControllerEntity
{

  Camera* m_editorCamera;
  SharedPtr<InputMapping> m_editorBindings;
};

