#pragma once

#include "uiPrerequisites.h"

#include "uiInput.h"

// template<typename ReturnType, typename... Args>
using InputCallback = Callback<void, SharedPtr<InputValue>>;

class InputAction
{
public:

  InputAction() = default;

  InputAction(const String& name, 
              const String& description)
  : m_name(name),
    m_description(description) {}

  ~InputAction() = default;


  uint32 GetHashID() { return static_cast<uint32>(Hash<String>()(m_name)); }

  String m_name;
  String m_description;

  InputCallback m_action;
};