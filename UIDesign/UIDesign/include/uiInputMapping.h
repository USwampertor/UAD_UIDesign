#pragma once

#include "uiPrerequisites.h"

#include "uiUtilities.h"
#include "uiInput.h"
#include "uiInputAction.h"

// #include <gainput/gainput.h>

class InputMapping // : public gainput::InputMap
{
public:
  InputMapping() = default;// (InputManager& manager, const String& name = 0)
    // : gainput::InputMap(manager, name.c_str()) {}

  ~InputMapping() = default;

  void BindAction(SharedPtr<InputAction> action, Input::eINPUTCODE button);

  void CreateFloatAction();

  void CreateBoolAction();

  void RemoveAction(const String& actionName);

  void OnInputUpdated(const Input::eINPUTCODE& code);

  void Enable();

  void Disable();

  Map<Input::eINPUTCODE, SharedPtr<InputAction>> m_actions;

  bool m_enabled;
};

