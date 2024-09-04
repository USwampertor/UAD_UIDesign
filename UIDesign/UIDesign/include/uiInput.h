#pragma once

#include "uiModule.h"
#include "uiPrerequisites.h"
#include "uiUtilities.h"

#include <SFML/Window.hpp>


class InputMapping;

namespace Input
{
  using Joystick    = sf::Joystick;
  using Keyboard    = sf::Keyboard;
  using Mouse       = sf::Mouse;
  using DeviceData  = sf::Joystick::Identification;
  
  BETTER_ENUM(
    eINPUTSTATE, 
    uint32, 
    PRESSED,
    HELD,
    RELEASED,
    INACTIVE 
  )

  BETTER_ENUM(
    eDEVICEHEXVALUE, 
    uint32,
    MOUSE = 1,
    JOYSTICK,
    KEYBOARD,
    KEYSCAN 
  )

  BETTER_ENUM(
    eINPUTCODE, 
    int64,
    MouseLeft                       = 0x001,
    MouseRight                      = 0x011,
    MouseMiddle                     = 0x021,
    MouseXButton1                   = 0x031,
    MouseXButton2                   = 0x041,
    MouseWheelVertical              = 0x051,
    MouseWheelHorizontal            = 0x061,
    JoystickAxisX                   = 0x002,
    JoystickAxisY                   = 0x012,
    JoystickAxisZ                   = 0x022,
    JoystickAxisR                   = 0x032,
    JoystickAxisU                   = 0x042,
    JoystickAxisV                   = 0x052,
    JoystickAxisHatX                = 0x062,
    JoystickAxisHatY                = 0x072,
    KeyCodeUnknown                  = 0xF03,
    KeyCodeA                        = 0x003,
    KeyCodeB                        = 0x013,            
    KeyCodeC                        = 0x023,            
    KeyCodeD                        = 0x033,            
    KeyCodeE                        = 0x043,            
    KeyCodeF                        = 0x053,            
    KeyCodeG                        = 0x063,            
    KeyCodeH                        = 0x073,            
    KeyCodeI                        = 0x083,            
    KeyCodeJ                        = 0x093,            
    KeyCodeK                        = 0x0A3,            
    KeyCodeL                        = 0x0B3,            
    KeyCodeM                        = 0x0C3,            
    KeyCodeN                        = 0x0D3,            
    KeyCodeO                        = 0x0E3,            
    KeyCodeP                        = 0x0F3,            
    KeyCodeQ                        = 0x103,            
    KeyCodeR                        = 0x113,            
    KeyCodeS                        = 0x123,            
    KeyCodeT                        = 0x133,            
    KeyCodeU                        = 0x143,            
    KeyCodeV                        = 0x153,            
    KeyCodeW                        = 0x163,            
    KeyCodeX                        = 0x173,            
    KeyCodeY                        = 0x183,            
    KeyCodeZ                        = 0x193,          
    KeyCodeNum0                     = 0x1A3,         
    KeyCodeNum1                     = 0x1B3,         
    KeyCodeNum2                     = 0x1C3,         
    KeyCodeNum3                     = 0x1D3,         
    KeyCodeNum4                     = 0x1E3,         
    KeyCodeNum5                     = 0x1F3,         
    KeyCodeNum6                     = 0x203,         
    KeyCodeNum7                     = 0x213,         
    KeyCodeNum8                     = 0x223,         
    KeyCodeNum9                     = 0x233,         
    KeyCodeEscape                   = 0x243,
    KeyCodeLControl                 = 0x253,
    KeyCodeLShift                   = 0x263,
    KeyCodeLAlt                     = 0x273,
    KeyCodeLSystem                  = 0x283,
    KeyCodeRControl                 = 0x293,
    KeyCodeRShift                   = 0x2A3,
    KeyCodeRAlt                     = 0x2B3,
    KeyCodeRSystem                  = 0x2C3,
    KeyCodeMenu                     = 0x2D3,
    KeyCodeLBracket                 = 0x2E3,
    KeyCodeRBracket                 = 0x2F3,
    KeyCodeSemicolon                = 0x303
    )/*
    KeyCodeComma                    = 0x313,
    KeyCodePeriod                   = 0x323,
    KeyCodeApostrophe               = 0x343,
    KeyCodeSlash                    = 0x353,
    KeyCodeBackslash                = 0x363,
    KeyCodeGrave                    = 0x373,
    KeyCodeEqual                    = 0x383,
    KeyCodeHyphen                   = 0x393,
    KeyCodeSpace                    = 0x3A3,
    KeyCodeEnter                    = 0x3B3,
    KeyCodeBackspace                = 0x3C3,
    KeyCodeTab                      = 0x3D3,
    KeyCodePageUp                   = 0x3E3,
    KeyCodePageDown                 = 0x3F3,
    KeyCodeEnd                      = 0x403,
    KeyCodeHome                     = 0x413,
    KeyCodeInsert                   = 0x423,
    KeyCodeDelete                   = 0x433,
    KeyCodeAdd                      = 0x443,
    KeyCodeSubtract                 = 0x453,
    KeyCodeMultiply                 = 0x463,
    KeyCodeDivide                   = 0x473,
    KeyCodeLeft                     = 0x483,
    KeyCodeRight                    = 0x493,
    KeyCodeUp                       = 0x4A3,
    KeyCodeDown                     = 0x4B3,
    KeyCodeNumpad0                  = 0x4C3,      
    KeyCodeNumpad1                  = 0x4D3,      
    KeyCodeNumpad2                  = 0x4E3,      
    KeyCodeNumpad3                  = 0x4F3,      
    KeyCodeNumpad4                  = 0x503,      
    KeyCodeNumpad5                  = 0x513,      
    KeyCodeNumpad6                  = 0x523,      
    KeyCodeNumpad7                  = 0x533,      
    KeyCodeNumpad8                  = 0x543,      
    KeyCodeNumpad9                  = 0x553,      
    KeyCodeF1                       = 0x563,           
    KeyCodeF2                       = 0x573,           
    KeyCodeF3                       = 0x583,           
    KeyCodeF4                       = 0x593,           
    KeyCodeF5                       = 0x5A3,           
    KeyCodeF6                       = 0x5B3,           
    KeyCodeF7                       = 0x5C3,           
    KeyCodeF8                       = 0x5D3,           
    KeyCodeF9                       = 0x5E3,           
    KeyCodeF10                      = 0x5F3,          
    KeyCodeF11                      = 0x603,          
    KeyCodeF12                      = 0x613,          
    KeyCodeF13                      = 0x623,          
    KeyCodeF14                      = 0x633,          
    KeyCodeF15                      = 0x643,          
    KeyCodePause                    = 0x653,        
    KeyScanUnknown                  = 0xF04,
    KeyScanA                        = 0x004,
    KeyScanB                        = 0x014,
    KeyScanC                        = 0x024,
    KeyScanD                        = 0x034,
    KeyScanE                        = 0x044,
    KeyScanF                        = 0x054,
    KeyScanG                        = 0x064,
    KeyScanH                        = 0x074,
    KeyScanI                        = 0x084,
    KeyScanJ                        = 0x094,
    KeyScanK                        = 0x0A4,
    KeyScanL                        = 0x0B4,
    KeyScanM                        = 0x0C4,
    KeyScanN                        = 0x0D4,
    KeyScanO                        = 0x0E4,
    KeyScanP                        = 0x0F4,
    KeyScanQ                        = 0x104,
    KeyScanR                        = 0x114,
    KeyScanS                        = 0x124,
    KeyScanT                        = 0x134,
    KeyScanU                        = 0x144,
    KeyScanV                        = 0x154,
    KeyScanW                        = 0x164,
    KeyScanX                        = 0x174,
    KeyScanY                        = 0x184,
    KeyScanZ                        = 0x194,
    KeyScanNum1                     = 0x1A4,
    KeyScanNum2                     = 0x1B4,
    KeyScanNum3                     = 0x1C4,
    KeyScanNum4                     = 0x1D4,
    KeyScanNum5                     = 0x1E4,
    KeyScanNum6                     = 0x1F4,
    KeyScanNum7                     = 0x104,
    KeyScanNum8                     = 0x114,
    KeyScanNum9                     = 0x124,
    KeyScanNum0                     = 0x134,
    KeyScanEnter                    = 0x144,
    KeyScanEscape                   = 0x154,
    KeyScanBackspace                = 0x164,
    KeyScanTab                      = 0x174,
    KeyScanSpace                    = 0x184,
    KeyScanHyphen                   = 0x194,
    KeyScanEqual                    = 0x1A4,
    KeyScanLBracket                 = 0x1B4,
    KeyScanRBracket                 = 0x1C4,
    KeyScanBackslash                = 0x1D4,
    KeyScanSemicolon                = 0x1E4,
    KeyScanApostrophe               = 0x1F4,
    KeyScanGrave                    = 0x204,
    KeyScanComma                    = 0x214,
    KeyScanPeriod                   = 0x224,
    KeyScanSlash                    = 0x234,
    KeyScanF1                       = 0x244,
    KeyScanF2                       = 0x254,
    KeyScanF3                       = 0x264,
    KeyScanF4                       = 0x274,
    KeyScanF5                       = 0x284,
    KeyScanF6                       = 0x294,
    KeyScanF7                       = 0x2A4,
    KeyScanF8                       = 0x2B4,
    KeyScanF9                       = 0x2C4,
    KeyScanF10                      = 0x2D4,
    KeyScanF11                      = 0x2E4,
    KeyScanF12                      = 0x2F4,
    KeyScanF13                      = 0x304,
    KeyScanF14                      = 0x314,
    KeyScanF15                      = 0x324,
    KeyScanF16                      = 0x334,
    KeyScanF17                      = 0x344,
    KeyScanF18                      = 0x354,
    KeyScanF19                      = 0x364,
    KeyScanF20                      = 0x374,
    KeyScanF21                      = 0x384,
    KeyScanF22                      = 0x394,
    KeyScanF23                      = 0x3A4,
    KeyScanF24                      = 0x3B4,
    KeyScanCapsLock                 = 0x3C4,
    KeyScanPrintScreen              = 0x3D4,
    KeyScanScrollLock               = 0x3E4,
    KeyScanPause                    = 0x3F4,
    KeyScanInsert                   = 0x404,
    KeyScanHome                     = 0x414,
    KeyScanPageUp                   = 0x424,
    KeyScanDelete                   = 0x434,
    KeyScanEnd                      = 0x444,
    KeyScanPageDown                 = 0x454,
    KeyScanRight                    = 0x464,
    KeyScanLeft                     = 0x474,
    KeyScanDown                     = 0x484,
    KeyScanUp                       = 0x494,
    KeyScanNumLock                  = 0x4A4,
    KeyScanNumpadDivide             = 0x4B4,
    KeyScanNumpadMultiply           = 0x4C4,
    KeyScanNumpadMinus              = 0x4D4,
    KeyScanNumpadPlus               = 0x4E4,
    KeyScanNumpadEqual              = 0x4F4,
    KeyScanNumpadEnter              = 0x504,
    KeyScanNumpadDecimal            = 0x514,
    KeyScanNumpad1                  = 0x524,
    KeyScanNumpad2                  = 0x534,
    KeyScanNumpad3                  = 0x544,
    KeyScanNumpad4                  = 0x554,
    KeyScanNumpad5                  = 0x564,
    KeyScanNumpad6                  = 0x574,
    KeyScanNumpad7                  = 0x584,
    KeyScanNumpad8                  = 0x594,
    KeyScanNumpad9                  = 0x5A4,
    KeyScanNumpad0                  = 0x5B4,
    KeyScanNonUsBackslash           = 0x5C4,
    KeyScanApplication              = 0x5D4,
    KeyScanExecute                  = 0x5E4,
    KeyScanModeChange               = 0x5F4,
    KeyScanHelp                     = 0x604,
    KeyScanMenu                     = 0x614,
    KeyScanSelect                   = 0x624,
    KeyScanRedo                     = 0x634,
    KeyScanUndo                     = 0x644,
    KeyScanCut                      = 0x654,
    KeyScanCopy                     = 0x664,
    KeyScanPaste                    = 0x674,
    KeyScanVolumeMute               = 0x684,
    KeyScanVolumeUp                 = 0x694,
    KeyScanVolumeDown               = 0x6A4,
    KeyScanMediaPlayPause           = 0x6B4,
    KeyScanMediaStop                = 0x6C4,
    KeyScanMediaNextTrack           = 0x6D4,
    KeyScanMediaPreviousTrack       = 0x6E4,
    KeyScanLControl                 = 0x6F4,
    KeyScanLShift                   = 0x704,
    KeyScanLAlt                     = 0x714,
    KeyScanLSystem                  = 0x724,
    KeyScanRControl                 = 0x734,
    KeyScanRShift                   = 0x744,
    KeyScanRAlt                     = 0x754,
    KeyScanRSystem                  = 0x764,
    KeyScanBack                     = 0x774,
    KeyScanForward                  = 0x784,
    KeyScanRefresh                  = 0x794,
    KeyScanStop                     = 0x7A4,
    KeyScanSearch                   = 0x7B4,
    KeyScanFavorites                = 0x7C4,
    KeyScanHomePage                 = 0x7D4,
    KeyScanLaunchApplication1       = 0x7E4,
    KeyScanLaunchApplication2       = 0x7F4,
    KeyScanLaunchMail               = 0x804,
    KeyScanLaunchMediaSelect        = 0x814


   */
// using eINPUTSTATE     = uint32;
// using eINPUTCODE      = uint32;
// using eDEVICEHEXVALUE = uint32;

}

struct InputValue
{
  Input::eINPUTSTATE m_state;
  
  const Input::eINPUTSTATE& GetState()
  {
    return m_state;
  }

  const Input::eINPUTSTATE& UpdateState(const Input::eINPUTSTATE& newValue)
  {
    m_state = newValue;
  }

  void* ReadRaw()
  {
    return m_value;
  }
  
  template<typename T>
  const T& ReadValue()
  {
    return reinterpret_cast<T>(m_value);
  }

  void UpdateValue(void* newValue)
  {
    m_value = m_value;
  }

  float m_timePressed;

  float m_timeInactive;

  void* m_value;
};

class InputManager : public Module<InputManager>
{
public:
  void Update(const float& delta)
  {
    // for (uint64 i = 0; i < Input::eINPUTCODE::_size(); ++i)
    // {
    // 
    // }


    // Keyboard Checking
    for (int i = 0; i < Input::Keyboard::KeyCount; ++i)
    {
      // Input::eINPUTCODE c = SFMLtoInputCode(Input::eDEVICEHEXVALUE::KEYBOARD, i);
      // if (sf::Keyboard::isKeyPressed(i))
      // {
      //   if (m_values[c].m_state == Input::eINPUTSTATE::INVALID)
      //   {
      //     m_values[c].UpdateState(Input::eINPUTSTATE::PRESSED);
      //   }
      // 
      // }
      // else if (sf::Keyboard::isKeyPressed(i))
      // {
      // 
      // }
    }

    // Mouse Checking


    // Joystick Checking

    //
  }

  Input::eINPUTCODE SFMLtoInputCode(const uint32& device, const uint32& inputCode)
  {
    return Input::eINPUTCODE::_from_integral((inputCode < 0 ? 15 : 0) << 16 | (inputCode << 4) | (device));
  }

  Vector2i GetScreenMousePosition() { return Input::Mouse::getPosition(); }
  
  Vector2i GetWindowMousePosition(const sf::Window& w) { return Input::Mouse::getPosition(w); }

  void SetScreenMousePosition(const Vector2i& pos) { Input::Mouse::setPosition(pos); }

  void SetWindowMousePosition(const Vector2i& pos, const sf::Window& w) { Input::Mouse::setPosition(pos, w); }

  void RegisterJoystick(const int& value = 1);

  void RemoveJoystic();

  void NotifyKeyPressed();

  SharedPtr<InputMapping> m_maps;

  Map<Input::eINPUTCODE, InputValue> m_values;

  uint32 m_joysticks;

};

/*
class InputManager : public gainput::InputManager , public Module<InputManager>
{
public:
  virtual void OnStartUp() override
  {
    m_mouse = CreateDevice<InputMouse>();
    m_keyboard = CreateDevice<InputKeyboard>();
  }

  DeviceID AddJoystick(const uint32& num = 1);

  DeviceID RemoveJoystick(const uint32& num);

  DeviceID GetMouseID();

  DeviceID GetKeyboardID();

  DeviceID GetJoystickID(const uint32& num);

  InputMouse GetMouse();

  InputKeyboard GetKeyboard();

  InputJoystick GetJoystick(const uint32 num);

  Vector<DeviceID> m_joysticks;

  DeviceID m_keyboard;

  DeviceID m_mouse;
};
*/

