#pragma once

#include "uiPrerequisites.h"

#include "uiInput.h"
#include "uiUtilities.h"


using InputCallback = std::function<void(InputValue)>;

class InputAction
{
public:

  InputAction() = default;

  InputAction(const String& name, 
              const String& description, 
              const InputCallback& callback)
  : m_name(name),
    m_description(description),
    m_action(callback) {}

  InputAction(const String& name, const String& description)
    : m_name(name),
      m_description(description) {}

  ~InputAction() = default;


  uint32 GetHashID() { return static_cast<uint32>(Hash<String>()(m_name)); }

  String m_name;
  String m_description;
  InputCallback m_action;
};