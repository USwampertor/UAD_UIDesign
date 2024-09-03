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

  BETTER_ENUM(eINPUTSTATE, uint32, 
    Pressed,
    Held,
    Released,
    Inactive
  )

  BETTER_ENUM(eDEVICEHEXCODE, uint32,
    MOUSE = 1,
    JOYSTICK,
    KEYBOARD,
    KEYSCAN
  )

  BETTER_ENUM(eINPUTCODE, int64,
    MouseLeft                       = 0x000001,
    MouseRight                      = 0x000011,
    MouseMiddle                     = 0x000021,
    MouseXButton1                   = 0x000031,
    MouseXButton2                   = 0x000041,
    MouseWheelVertical              = 0x000051,
    MouseWheelHorizontal            = 0x000061,
    JoystickAxisX                   = 0x000002,
    JoystickAxisY                   = 0x000012,
    JoystickAxisZ                   = 0x000022,
    JoystickAxisR                   = 0x000032,
    JoystickAxisU                   = 0x000042,
    JoystickAxisV                   = 0x000052,
    JoystickAxisHatX                = 0x000062,
    JoystickAxisHatY                = 0x000072,
    KeyCodeUnknown                  = 0xF00013,
    KeyCodeA                        = 0x000003,
    KeyCodeB                        = 0x000013,            
    KeyCodeC                        = 0x000023,            
    KeyCodeD                        = 0x000033,            
    KeyCodeE                        = 0x000043,            
    KeyCodeF                        = 0x000053,            
    KeyCodeG                        = 0x000063,            
    KeyCodeH                        = 0x000073,            
    KeyCodeI                        = 0x000083,            
    KeyCodeJ                        = 0x000093,            
    KeyCodeK                        = 0x0000A3,            
    KeyCodeL                        = 0x0000B3,            
    KeyCodeM                        = 0x0000C3,            
    KeyCodeN                        = 0x0000D3,            
    KeyCodeO                        = 0x0000E3,            
    KeyCodeP                        = 0x0000F3,            
    KeyCodeQ                        = 0x000103,            
    KeyCodeR                        = 0x000113,            
    KeyCodeS                        = 0x000123,            
    KeyCodeT                        = 0x000133,            
    KeyCodeU                        = 0x000143,            
    KeyCodeV                        = 0x000153,            
    KeyCodeW                        = 0x000163,            
    KeyCodeX                        = 0x000173,            
    KeyCodeY                        = 0x000183,            
    KeyCodeZ                        = 0x000193,            
    KeyCodeNum0                     = 0x0001A3,         
    KeyCodeNum1                     = 0x0001B3,         
    KeyCodeNum2                     = 0x0001C3,         
    KeyCodeNum3                     = 0x0001D3,         
    KeyCodeNum4                     = 0x0001E3,         
    KeyCodeNum5                     = 0x0001F3,         
    KeyCodeNum6                     = 0x000203,         
    KeyCodeNum7                     = 0x000213,         
    KeyCodeNum8                     = 0x000223,         
    KeyCodeNum9                     = 0x000233,         
    KeyCodeEscape                   = 0x000243,
    KeyCodeLControl                 = 0x000253,
    KeyCodeLShift                   = 0x000263,
    KeyCodeLAlt                     = 0x000273,
    KeyCodeLSystem                  = 0x000283,
    KeyCodeRControl                 = 0x000293,
    KeyCodeRShift                   = 0x0002A3,
    KeyCodeRAlt                     = 0x0002B3,
    KeyCodeRSystem                  = 0x0002C3,
    KeyCodeMenu                     = 0x0002D3,
    KeyCodeLBracket                 = 0x0002E3,
    KeyCodeRBracket                 = 0x0002F3,
    KeyCodeSemicolon                = 0x000303,
    KeyCodeComma                    = 0x000313,
    KeyCodePeriod                   = 0x000323,
    KeyCodeApostrophe               = 0x000343,
    KeyCodeSlash                    = 0x000353,
    KeyCodeBackslash                = 0x000363,
    KeyCodeGrave                    = 0x000373,
    KeyCodeEqual                    = 0x000383,
    KeyCodeHyphen                   = 0x000393,
    KeyCodeSpace                    = 0x0003A3,
    KeyCodeEnter                    = 0x0003B3,
    KeyCodeBackspace                = 0x0003C3,
    KeyCodeTab                      = 0x0003D3,
    KeyCodePageUp                   = 0x0003E3,
    KeyCodePageDown                 = 0x0003F3,
    KeyCodeEnd                      = 0x000403,
    KeyCodeHome                     = 0x000413,
    KeyCodeInsert                   = 0x000423,
    KeyCodeDelete                   = 0x000433,
    KeyCodeAdd                      = 0x000443,
    KeyCodeSubtract                 = 0x000453,
    KeyCodeMultiply                 = 0x000463,
    KeyCodeDivide                   = 0x000473,
    KeyCodeLeft                     = 0x000483,
    KeyCodeRight                    = 0x000493,
    KeyCodeUp                       = 0x0004A3,
    KeyCodeDown                     = 0x0004B3,
    KeyCodeNumpad0                  = 0x0004C3,      
    KeyCodeNumpad1                  = 0x0004D3,      
    KeyCodeNumpad2                  = 0x0004E3,      
    KeyCodeNumpad3                  = 0x0004F3,      
    KeyCodeNumpad4                  = 0x000503,      
    KeyCodeNumpad5                  = 0x000513,      
    KeyCodeNumpad6                  = 0x000523,      
    KeyCodeNumpad7                  = 0x000533,      
    KeyCodeNumpad8                  = 0x000543,      
    KeyCodeNumpad9                  = 0x000553,      
    KeyCodeF1                       = 0x000563,           
    KeyCodeF2                       = 0x000573,           
    KeyCodeF3                       = 0x000583,           
    KeyCodeF4                       = 0x000593,           
    KeyCodeF5                       = 0x0005A3,           
    KeyCodeF6                       = 0x0005B3,           
    KeyCodeF7                       = 0x0005C3,           
    KeyCodeF8                       = 0x0005D3,           
    KeyCodeF9                       = 0x0005E3,           
    KeyCodeF10                      = 0x0005F3,          
    KeyCodeF11                      = 0x000603,          
    KeyCodeF12                      = 0x000613,          
    KeyCodeF13                      = 0x000623,          
    KeyCodeF14                      = 0x000633,          
    KeyCodeF15                      = 0x000643,          
    KeyCodePause                    = 0x000653,        
    KeyScanUnknown                  = 0xF00334,
    KeyScanA                        = 0x000004,
    KeyScanB                        = 0x000014,
    KeyScanC                        = 0x000024,
    KeyScanD                        = 0x000034,
    KeyScanE                        = 0x000044,
    KeyScanF                        = 0x000054,
    KeyScanG                        = 0x000064,
    KeyScanH                        = 0x000074,
    KeyScanI                        = 0x000084,
    KeyScanJ                        = 0x000094,
    KeyScanK                        = 0x0000A4,
    KeyScanL                        = 0x0000B4,
    KeyScanM                        = 0x0000C4,
    KeyScanN                        = 0x0000D4,
    KeyScanO                        = 0x0000E4,
    KeyScanP                        = 0x0000F4,
    KeyScanQ                        = 0x000104,
    KeyScanR                        = 0x000114,
    KeyScanS                        = 0x000124,
    KeyScanT                        = 0x000134,
    KeyScanU                        = 0x000144,
    KeyScanV                        = 0x000154,
    KeyScanW                        = 0x000164,
    KeyScanX                        = 0x000174,
    KeyScanY                        = 0x000184,
    KeyScanZ                        = 0x000194,
    KeyScanNum1                     = 0x0001A4,
    KeyScanNum2                     = 0x0001B4,
    KeyScanNum3                     = 0x0001C4,
    KeyScanNum4                     = 0x0001D4,
    KeyScanNum5                     = 0x0001E4,
    KeyScanNum6                     = 0x0001F4,
    KeyScanNum7                     = 0x000104,
    KeyScanNum8                     = 0x000114,
    KeyScanNum9                     = 0x000124,
    KeyScanNum0                     = 0x000134,
    KeyScanEnter                    = 0x000144,
    KeyScanEscape                   = 0x000154,
    KeyScanBackspace                = 0x000164,
    KeyScanTab                      = 0x000174,
    KeyScanSpace                    = 0x000184,
    KeyScanHyphen                   = 0x000194,
    KeyScanEqual                    = 0x0001A4,
    KeyScanLBracket                 = 0x0001B4,
    KeyScanRBracket                 = 0x0001C4,
    KeyScanBackslash                = 0x0001D4,
    KeyScanSemicolon                = 0x0001E4,
    KeyScanApostrophe               = 0x0001F4,
    KeyScanGrave                    = 0x000204,
    KeyScanComma                    = 0x000214,
    KeyScanPeriod                   = 0x000224,
    KeyScanSlash                    = 0x000234,
    KeyScanF1                       = 0x000244,
    KeyScanF2                       = 0x000254,
    KeyScanF3                       = 0x000264,
    KeyScanF4                       = 0x000274,
    KeyScanF5                       = 0x000284,
    KeyScanF6                       = 0x000294,
    KeyScanF7                       = 0x0002A4,
    KeyScanF8                       = 0x0002B4,
    KeyScanF9                       = 0x0002C4,
    KeyScanF10                      = 0x0002D4,
    KeyScanF11                      = 0x0002E4,
    KeyScanF12                      = 0x0002F4,
    KeyScanF13                      = 0x000304,
    KeyScanF14                      = 0x000314,
    KeyScanF15                      = 0x000324,
    KeyScanF16                      = 0x000334,
    KeyScanF17                      = 0x000344,
    KeyScanF18                      = 0x000354,
    KeyScanF19                      = 0x000364,
    KeyScanF20                      = 0x000374,
    KeyScanF21                      = 0x000384,
    KeyScanF22                      = 0x000394,
    KeyScanF23                      = 0x0003A4,
    KeyScanF24                      = 0x0003B4,
    KeyScanCapsLock                 = 0x0003C4,
    KeyScanPrintScreen              = 0x0003D4,
    KeyScanScrollLock               = 0x0003E4,
    KeyScanPause                    = 0x0003F4,
    KeyScanInsert                   = 0x000404,
    KeyScanHome                     = 0x000414,
    KeyScanPageUp                   = 0x000424,
    KeyScanDelete                   = 0x000434,
    KeyScanEnd                      = 0x000444,
    KeyScanPageDown                 = 0x000454,
    KeyScanRight                    = 0x000464,
    KeyScanLeft                     = 0x000474,
    KeyScanDown                     = 0x000484,
    KeyScanUp                       = 0x000494,
    KeyScanNumLock                  = 0x0004A4,
    KeyScanNumpadDivide             = 0x0004B4,
    KeyScanNumpadMultiply           = 0x0004C4,
    KeyScanNumpadMinus              = 0x0004D4,
    KeyScanNumpadPlus               = 0x0004E4,
    KeyScanNumpadEqual              = 0x0004F4,
    KeyScanNumpadEnter              = 0x000504,
    KeyScanNumpadDecimal            = 0x000514,
    KeyScanNumpad1                  = 0x000524,
    KeyScanNumpad2                  = 0x000534,
    KeyScanNumpad3                  = 0x000544,
    KeyScanNumpad4                  = 0x000554,
    KeyScanNumpad5                  = 0x000564,
    KeyScanNumpad6                  = 0x000574,
    KeyScanNumpad7                  = 0x000584,
    KeyScanNumpad8                  = 0x000594,
    KeyScanNumpad9                  = 0x0005A4,
    KeyScanNumpad0                  = 0x0005B4,
    KeyScanNonUsBackslash           = 0x0005C4,
    KeyScanApplication              = 0x0005D4,
    KeyScanExecute                  = 0x0005E4,
    KeyScanModeChange               = 0x0005F4,
    KeyScanHelp                     = 0x000604,
    KeyScanMenu                     = 0x000614,
    KeyScanSelect                   = 0x000624,
    KeyScanRedo                     = 0x000634,
    KeyScanUndo                     = 0x000644,
    KeyScanCut                      = 0x000654,
    KeyScanCopy                     = 0x000664,
    KeyScanPaste                    = 0x000674,
    KeyScanVolumeMute               = 0x000684,
    KeyScanVolumeUp                 = 0x000694,
    KeyScanVolumeDown               = 0x0006A4,
    KeyScanMediaPlayPause           = 0x0006B4,
    KeyScanMediaStop                = 0x0006C4,
    KeyScanMediaNextTrack           = 0x0006D4,
    KeyScanMediaPreviousTrack       = 0x0006E4,
    KeyScanLControl                 = 0x0006F4,
    KeyScanLShift                   = 0x000704,
    KeyScanLAlt                     = 0x000714,
    KeyScanLSystem                  = 0x000724,
    KeyScanRControl                 = 0x000734,
    KeyScanRShift                   = 0x000744,
    KeyScanRAlt                     = 0x000754,
    KeyScanRSystem                  = 0x000764,
    KeyScanBack                     = 0x000774,
    KeyScanForward                  = 0x000784,
    KeyScanRefresh                  = 0x000794,
    KeyScanStop                     = 0x0007A4,
    KeyScanSearch                   = 0x0007B4,
    KeyScanFavorites                = 0x0007C4,
    KeyScanHomePage                 = 0x0007D4,
    KeyScanLaunchApplication1       = 0x0007E4,
    KeyScanLaunchApplication2       = 0x0007F4,
    KeyScanLaunchMail               = 0x000804,
    KeyScanLaunchMediaSelect        = 0x000814,
  )

}

class InputValue
{
  Input::
};

class InputManager : public Module<InputManager>
{
  void Update(const float& delta)
  {
    // Keyboard Checking
    for (int i = 0; i < Keyboard::KeyCount; ++i)
    {
      Input::InputCode c = SFMLtoInputCode(Input::DEVICEHEXVALUE::KEYBOARD, )
      if (sf::Keyboard::isKeyPressed(i))
      {
        
      }
    }

    // Mouse Checking


    // Joystick Checking

    //
  }

  Input::InputCode SFMLtoInputCode(const uint32& device, const uint32& inputCode)
  {
    return Input::InputCode::_from_integral((inputCode < 0 ? 15 : 0) << 20 | (inputCode << 4) | (device));
  }

  Vector2i GetGlobalMousePosition() { return Input::Mouse::getPosition(); }
  
  Vector2i GetWindowMousePosition(const sf::Window& w) { return Input::Mouse::getPosition(w); }

  void SetGlobalMousePosition(const Vector2i& pos) { Input::Mouse::setPosition(pos); }

  void SetWindowMousePosition(const Vector2i& pos, const Window& w) { Input::Mouse::setPosition(pos, w); }

  void RegisterJoystick();

  void RemoveJoystic();

  void NotifyKeyPressed();

  SharedPtr<InputMapping>
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

