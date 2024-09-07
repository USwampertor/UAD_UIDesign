#include "uiInputMapping.h"

#include "uiEntity.h"

void InputMapping::OnInputUpdated(const Input::eINPUTCODE& code, const SharedPtr<InputValue> v)
{
  if (m_actions.find(code) != m_actions.end())
  {
    m_actions[code]->m_action(v);
  }
}
// template <typename Callable>
void InputMapping::BindAction(Input::eINPUTCODE button, const InputCallback& c)
{
  if (m_actions.find(button) == m_actions.end())
  {
    SharedPtr<InputAction> newAction = MakeSharedObject<InputAction>();
    newAction->m_action = c;
    m_actions.insert(Utils::MakePair(button, newAction));
  }
}

void InputMapping::RemoveAction(Input::eINPUTCODE button)
{
  if (m_actions.find(button) != m_actions.end())
  {
    m_actions.erase(button);
  }
}

// void InputMapping::BindAction(Input::eINPUTCODE button, SharedPtr<Entity>& obj, InputCallback& c)
// {
//   if (m_actions.find(button) == m_actions.end())
//   {
//     // action->m_action = std::bind(c, obj);
//     // SharedPtr<InputAction> action = MakeSharedObject<InputAction>();
//     // action->m_action = std::bind(c, obj, std::placeholders::_1);
//     // m_actions.insert(Utils::MakePair(button, action));
//   }
// }
