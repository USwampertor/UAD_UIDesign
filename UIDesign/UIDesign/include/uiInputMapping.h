#pragma once

#include "uiUtilities.h"
#include "uiInput.h"
#include "uiInputAction.h"

// #include <gainput/gainput.h>

class InputMapping // : public gainput::InputMap
{
public:
  InputMapping(InputManager& manager, const String& name = 0)
    : gainput::InputMap(manager, name.c_str()) {}

  template <typename T>
  void BindAction(SharedPtr<InputAction> action, T button);

  void CreateFloatAction();

  void CreateBoolAction();

  void RemoveAction(const String& actionName);

  // Map<uint32, SharedPtr<InputAction>> m_actions;
};

