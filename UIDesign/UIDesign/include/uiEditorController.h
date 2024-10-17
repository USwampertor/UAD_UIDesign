#pragma once
#include "uiPrerequisites.h"
#include "uiClassRegisters.h"

#include "uiController.h"
#include "uiInputMapping.h"

class Camera;

class EditorControllerEntity : public ControllerEntity
{
  static String GetType() { return "EditorControllerEntity"; }

  Camera* m_editorCamera;
  SharedPtr<InputMapping> m_editorBindings;
};

REGISTER_CLASS(EditorControllerEntity)
