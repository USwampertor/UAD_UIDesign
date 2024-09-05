#include "uiInputMapping.h"

void InputMapping::OnInputUpdated(const Input::eINPUTCODE& code)
{
  if m_actions.contains(code)
  {
    m_actions[code]->m_action;
  }
}

void InputMapping::BindAction(SharedPtr<InputAction> action, Input::eINPUTCODE button)
{
  if (m_actions.find(button) == m_actions.end())
  {
    m_actions.insert(Utils::MakePair(button, action));
  }
}
