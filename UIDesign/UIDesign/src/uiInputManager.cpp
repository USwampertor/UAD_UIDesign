#include "uiInputManager.h"

#include "uiInputMapping.h"

#include "uiWindowManager.h"

void InputManager::PollEvents(const sf::Event& e)
{
  if (e.type == sf::Event::MouseWheelScrolled)
  {
    if (e.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel)
    {
      m_values[Input::eINPUTCODE::MouseWheelVertical][0]->UpdateValue(e.mouseWheelScroll.delta);
    }
    else if (e.mouseWheelScroll.wheel == sf::Mouse::HorizontalWheel)
    {
      m_values[Input::eINPUTCODE::MouseWheelHorizontal][0]->UpdateValue(e.mouseWheelScroll.delta);
    }
  }
}

void InputManager::Update(const float& delta)
{
  if (!WindowManager::Instance().m_mainWindow.hasFocus())
  {
    return;
  }
  for (Input::eINPUTCODE i : Input::eINPUTCODE::_values())
  {
    auto tuple = InputCodeToSFML(i);
    Input::eDEVICEHEXVALUE value = Input::eDEVICEHEXVALUE::_from_integral(std::get<0>(tuple));
    int32 enumValue = std::get<1>(tuple);

    // Check for mouse values
    if (value == Input::eDEVICEHEXVALUE::MOUSE)
    {
      sf::Mouse::Button button = static_cast<sf::Mouse::Button>(enumValue);
      if (Input::Mouse::isButtonPressed(button))
      {
        // Check for previous states
        if (m_values[i][0]->m_state == Input::eINPUTSTATE::INACTIVE)
        {
          m_values[i][0]->UpdateState(Input::eINPUTSTATE::PRESSED);
          m_values[i][0]->m_timePressed = 0.0f;
          m_values[i][0]->m_timeInactive = 0.0f;
          NotifyInputChange(i, 0);
        }
        else if (m_values[i][0]->m_state == Input::eINPUTSTATE::PRESSED)
        {
          m_values[i][0]->UpdateState(Input::eINPUTSTATE::HELD);
          m_values[i][0]->m_timePressed += delta;
          NotifyInputChange(i, 0);
        }
        else if (m_values[i][0]->m_state == Input::eINPUTSTATE::HELD)
        {
          m_values[i][0]->m_timePressed += delta;
          NotifyInputChange(i, 0);
        }
      }
      else if (!Input::Mouse::isButtonPressed(button))
      {
        // Check for previous states
        if (m_values[i][0]->m_state == Input::eINPUTSTATE::HELD ||
          m_values[i][0]->m_state == Input::eINPUTSTATE::PRESSED)
        {
          m_values[i][0]->UpdateState(Input::eINPUTSTATE::RELEASED);
          m_values[i][0]->m_timePressed = 0.0f;
          m_values[i][0]->m_timeInactive = 0.0f;
          NotifyInputChange(i, 0);
        }
        else if (m_values[i][0]->m_state == Input::eINPUTSTATE::RELEASED)
        {
          m_values[i][0]->UpdateState(Input::eINPUTSTATE::INACTIVE);
          m_values[i][0]->m_timeInactive += delta;
          NotifyInputChange(i, 0);
        }
        else if (m_values[i][0]->m_state == Input::eINPUTSTATE::INACTIVE)
        {
          m_values[i][0]->m_timeInactive += delta;
          NotifyInputChange(i, 0);
        }
      }

    }
    else if (value == Input::eDEVICEHEXVALUE::JOYSTICK)
    {
      for (uint32 j = 0; j < m_joysticks; ++j)
      {
        if (Input::Joystick::isButtonPressed(j, enumValue))
        {
          // Check for previous states
          if (m_values[i][j]->m_state == Input::eINPUTSTATE::INACTIVE)
          {
            m_values[i][j]->UpdateState(Input::eINPUTSTATE::PRESSED);
            m_values[i][j]->m_timePressed = 0.0f;
            m_values[i][j]->m_timeInactive = 0.0f;
            NotifyInputChange(i, j);
          }
          else if (m_values[i][j]->m_state == Input::eINPUTSTATE::PRESSED)
          {
            m_values[i][j]->UpdateState(Input::eINPUTSTATE::HELD);
            m_values[i][j]->m_timePressed += delta;
            NotifyInputChange(i, j);
          }
          else if (m_values[i][j]->m_state == Input::eINPUTSTATE::HELD)
          {
            m_values[i][j]->m_timePressed += delta;
            NotifyInputChange(i, j);
          }
        }
        else if (!Input::Joystick::isButtonPressed(j, enumValue))
        {
          // Check for previous states
          if (m_values[i][j]->m_state == Input::eINPUTSTATE::HELD ||
            m_values[i][j]->m_state == Input::eINPUTSTATE::PRESSED)
          {
            m_values[i][j]->UpdateState(Input::eINPUTSTATE::RELEASED);
            m_values[i][j]->m_timePressed = 0.0f;
            m_values[i][j]->m_timeInactive = 0.0f;
            NotifyInputChange(i, j);
          }
          else if (m_values[i][j]->m_state == Input::eINPUTSTATE::RELEASED)
          {
            m_values[i][j]->UpdateState(Input::eINPUTSTATE::INACTIVE);
            m_values[i][j]->m_timeInactive += delta;
            NotifyInputChange(i, j);
          }
          else if (m_values[i][j]->m_state == Input::eINPUTSTATE::INACTIVE)
          {
            m_values[i][j]->m_timeInactive += delta;
            NotifyInputChange(i, j);
          }
        }
      }
    }
    // Mouse Scrolls
    else if (value == Input::eDEVICEHEXVALUE::JOYSTICKAXIS)
    {
      Input::Joystick::Axis axis = static_cast<Input::Joystick::Axis>(enumValue);

      for (uint32 j = 0; j < m_joysticks; ++j)
      {
        m_values[i][j]->UpdateValue(Input::Joystick::getAxisPosition(j, axis));
        NotifyInputChange(i, j);
      }
    }
    else if (value == Input::eDEVICEHEXVALUE::KEYBOARD)
    {
      Input::Keyboard::Key key = static_cast<Input::Keyboard::Key>(enumValue);
      if (Input::Keyboard::isKeyPressed(key))
      {
        // Check for previous states
        if (m_values[i][0]->m_state == Input::eINPUTSTATE::INACTIVE)
        {
          m_values[i][0]->UpdateState(Input::eINPUTSTATE::PRESSED);
          m_values[i][0]->m_timePressed = 0.0f;
          m_values[i][0]->m_timeInactive = 0.0f;
          NotifyInputChange(i, 0);
        }
        else if (m_values[i][0]->m_state == Input::eINPUTSTATE::PRESSED)
        {
          m_values[i][0]->UpdateState(Input::eINPUTSTATE::HELD);
          m_values[i][0]->m_timePressed += delta;
          NotifyInputChange(i, 0);
        }
        else if (m_values[i][0]->m_state == Input::eINPUTSTATE::HELD)
        {
          m_values[i][0]->m_timePressed += delta;
          NotifyInputChange(i, 0);
        }
      }
      else if (!Input::Keyboard::isKeyPressed(key))
      {
        // Check for previous states
        if (m_values[i][0]->m_state == Input::eINPUTSTATE::HELD ||
          m_values[i][0]->m_state == Input::eINPUTSTATE::PRESSED)
        {
          m_values[i][0]->UpdateState(Input::eINPUTSTATE::RELEASED);
          m_values[i][0]->m_timePressed = 0.0f;
          m_values[i][0]->m_timeInactive = 0.0f;
          NotifyInputChange(i, 0);
        }
        else if (m_values[i][0]->m_state == Input::eINPUTSTATE::RELEASED)
        {
          m_values[i][0]->UpdateState(Input::eINPUTSTATE::INACTIVE);
          m_values[i][0]->m_timeInactive += delta;
          NotifyInputChange(i, 0);
        }
        else if (m_values[i][0]->m_state == Input::eINPUTSTATE::INACTIVE)
        {
          m_values[i][0]->m_timeInactive += delta;
          NotifyInputChange(i, 0);
        }
      }
    }
  }

}

Tuple<int32, int32> InputManager::InputCodeToSFML(const Input::eINPUTCODE& hexCode)
{
  int32 hexValue = hexCode._to_integral();
  String str = Utils::IntToHex(hexValue);
  String deviceStr = str.substr(str.size() - 1);
  String inputStr = str.substr(0, str.size() - 1);
  //Set value as a full 32 bit object
  String prefixD(static_cast<SizeT>(8 - deviceStr.size()), '0');
  String prefixI(static_cast<SizeT>(8 - inputStr.size()), inputStr.size() > 6 ? 'F' : '0');
  int32 device = std::stoi(prefixD + deviceStr, nullptr, 16);
  uint32 keycode = std::stoul(prefixI + inputStr, nullptr, 16);
  return Tuple<int32, int32>(device, static_cast<int32>(keycode));
}

Input::eINPUTCODE InputManager::SFMLtoInputCode(const int32& device, const int32& inputCode)
{
  return Input::eINPUTCODE::_from_integral((inputCode < 0 ? 15 : 0) << 16 | (inputCode << 4) | (device));
}

void InputManager::RegisterJoystick(const uint32& value)
{
  m_joysticks += value;
  // m_joysticks = std::clamp(static_cast<uint32>(m_joysticks), 0, static_cast<uint32>(Input::Joystick::Count));
}

void InputManager::RemoveJoystic(const uint32& value)
{
  m_joysticks -= value;
  // m_joysticks = std::clamp(m_joysticks, 0, static_cast<uint32>(Input::Joystick::Count));
}

void InputManager::NotifyInputChange(const Input::eINPUTCODE& code, const uint32& device)
{
  for (const SharedPtr<InputMapping>& map : m_maps)
  {
    if (map->m_enabled)
    {
      map->OnInputUpdated(code, m_values[code][device]);
    }
  }
}

void InputManager::RegisterInputMapping(SharedPtr<InputMapping> newMap)
{
  if (std::find(m_maps.begin(), m_maps.end(), newMap) == std::end(m_maps))
  {
    m_maps.push_back(newMap);
  }
}

