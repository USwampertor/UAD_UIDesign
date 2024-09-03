#pragma once

#include "uiUtilities.h"
#include "uiPlatformTypes.h"

enum class eINPUTVALUE : uint32
{
  BOOL = 0,
  FLOAT,
  VECTOR2
};

class InputAction
{
public:

  InputAction() = default;

  InputAction(const String& name, 
              const String& description, 
              const eINPUTVALUE& value, 
              const Callback& callback)
  : m_name(name),
    m_description(description),
    m_valueType(value),
    m_action(callback) {}

  ~InputAction() = default;


  uint32 GetHashID() { return static_cast<uint32>(Hash<String>()(m_name) + Hash<eINPUTVALUE>()(m_valueType)); }

  String m_name;
  String m_description;
  eINPUTVALUE m_valueType;
  Callback m_action;
};