#pragma once

#include "uiPrerequisites.h"

#include "uiInput.h"
#include "uiInputAction.h"


class Entity;

// #include <gainput/gainput.h>

class InputMapping // : public gainput::InputMap
{
public:
  InputMapping() = default;// (InputManager& manager, const String& name = 0)
    // : gainput::InputMap(manager, name.c_str()) {}

  ~InputMapping() = default;

  // void BindAction(Input::eINPUTCODE button, SharedPtr<Entity>& obj, InputCallback& c);

  // template <typename Callable>
  void BindAction(Input::eINPUTCODE button, const InputCallback& c);

  void RemoveAction(Input::eINPUTCODE button);

  void OnInputUpdated(const Input::eINPUTCODE& code, const SharedPtr<InputValue> value);

  Map<Input::eINPUTCODE, SharedPtr<InputAction>> m_actions;

  bool m_enabled;
};

