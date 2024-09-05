#pragma once
#include "uiPrerequisites.h"
#include "uiUtilities.h"
#include "uiInput.h"

class InputManager : public Module<InputManager>
{
public:

  virtual void OnStartUp() override
  {
    for (Input::eINPUTCODE i : Input::eINPUTCODE::_values())
    {
      String hexName = i._to_string();
      auto tuple = InputCodeToSFML(i);
      Input::eDEVICEHEXVALUE value = Input::eDEVICEHEXVALUE::_from_integral(std::get<0>(tuple));
      int32 enumValue = std::get<1>(tuple);
      m_values.insert(std::make_pair(i, Vector<SharedPtr<InputValue>>()));
      if (value == Input::eDEVICEHEXVALUE::JOYSTICK || value == Input::eDEVICEHEXVALUE::JOYSTICKAXIS)
      {
        for (int j = 0; j < Input::Joystick::Count; ++j)
        {
          m_values[i].push_back(MakeSharedObject<InputValue>());
          m_values[i][j]->UpdateState(Input::eINPUTSTATE::INACTIVE);
        }
      }
      else
      {
        m_values[i].push_back(MakeSharedObject<InputValue>());
        m_values[i][0]->UpdateState(Input::eINPUTSTATE::INACTIVE);
      }
    }
  }

  void PollEvents(const sf::Event& e);

  void Update(const float& delta);

  Input::eINPUTCODE SFMLtoInputCode(const int32& device, const int32& inputCode);

  Tuple<int32, int32> InputCodeToSFML(const Input::eINPUTCODE&);

  Vector2i GetScreenMousePosition() { return Input::Mouse::getPosition(); }

  Vector2i GetWindowMousePosition(const sf::Window& w) { return Input::Mouse::getPosition(w); }

  void SetScreenMousePosition(const Vector2i& pos) { Input::Mouse::setPosition(pos); }

  void SetWindowMousePosition(const Vector2i& pos, const sf::Window& w) { Input::Mouse::setPosition(pos, w); }

  void RegisterJoystick(const uint32& value = 1);

  void RemoveJoystic(const uint32& value = 1);

  void NotifyInputChange(const Input::eINPUTCODE& code);

  void RegisterInputMapping(SharedPtr<InputMapping> newMap);


  Vector<SharedPtr<InputMapping>> m_maps;

  Map<Input::eINPUTCODE, Vector<SharedPtr<InputValue>>> m_values;

  uint32 m_joysticks;

};
