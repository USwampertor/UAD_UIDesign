#pragma once

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

  template <typename T>
  void BindAction(SharedPtr<InputAction> action, T button);

  void CreateFloatAction();

  void CreateBoolAction();

  void RemoveAction(const String& actionName);

  Map<Input::eINPUTCODE, SharedPtr<InputAction>> m_actions;
};

