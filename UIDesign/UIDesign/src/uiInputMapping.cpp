#include "uiInputMapping.h"

#include "uiEntity.h"

void InputMapping::OnInputUpdated(const Input::eINPUTCODE& code)
{
  if (m_actions.find(code) != m_actions.end())
  {
    m_actions[code]->m_action;
  }
}

void InputMapping::BindAction(SharedPtr<InputAction>& action, Input::eINPUTCODE button, SharedPtr<Entity>& obj, InputCallback& c)
{
  if (m_actions.find(button) == m_actions.end())
  {
    // action->m_action = std::bind(c, obj);
    m_actions.insert(Utils::MakePair(button, action));
  }
}
