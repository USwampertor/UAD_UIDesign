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

#pragma region InputState
  BETTER_ENUM(
    eINPUTSTATE,
    uint32,
    PRESSED,
    HELD,
    RELEASED,
    INACTIVE
  )
#pragma endregion InputState

#pragma region DeviceHexValue
  BETTER_ENUM(
    eDEVICEHEXVALUE,
    uint32,
    MOUSE = 1,
    MOUSEWHEEL,
    JOYSTICK,
    JOYSTICKAXIS,
    KEYBOARD,
    KEYSCAN
  )
#pragma endregion DeviceHexValue

#pragma region InputCode
  BETTER_ENUM(
    eINPUTCODE, 
    int32,
    // Mouse Buttons
    MouseLeft                       = 0x00000001,
    MouseRight                      = 0x00000011,
    MouseMiddle                     = 0x00000021,
    MouseXButton1                   = 0x00000031,
    MouseXButton2                   = 0x00000041,
    // Mouse Wheels                     
    MouseWheelVertical              = 0x00000002,
    MouseWheelHorizontal            = 0x00000012,
    // Joystick Buttons                 
    JoystickButton1                 = 0x00000003,
    JoystickButton2                 = 0x00000013,
    JoystickButton3                 = 0x00000023,
    JoystickButton4                 = 0x00000033,
    JoystickButton5                 = 0x00000043,
    JoystickButton6                 = 0x00000053,
    JoystickButton7                 = 0x00000063,
    JoystickButton8                 = 0x00000073,
    JoystickButton9                 = 0x00000083,
    JoystickButton10                = 0x00000093,
    JoystickButton11                = 0x000000A3,
    JoystickButton12                = 0x000000B3,
    JoystickButton13                = 0x000000C3,
    JoystickButton14                = 0x000000D3,
    JoystickButton15                = 0x000000E3,
    JoystickButton16                = 0x000000F3,
    JoystickButton17                = 0x00000103,
    JoystickButton18                = 0x00000113,
    JoystickButton19                = 0x00000123,
    JoystickButton20                = 0x00000133,
    JoystickButton21                = 0x00000143,
    JoystickButton22                = 0x00000153,
    JoystickButton23                = 0x00000163,
    JoystickButton24                = 0x00000173,
    JoystickButton25                = 0x00000183,
    JoystickButton26                = 0x00000193,
    JoystickButton27                = 0x000001A3,
    JoystickButton28                = 0x000001B3,
    JoystickButton29                = 0x000001C3,
    JoystickButton30                = 0x000001D3,
    JoystickButton31                = 0x000001E3,
    JoystickButton32                = 0x000001F3,
    // Joystick Axis                    
    JoystickAxisX                   = 0x00000004,
    JoystickAxisY                   = 0x00000014,
    JoystickAxisZ                   = 0x00000024,
    JoystickAxisR                   = 0x00000034,
    JoystickAxisU                   = 0x00000044,
    JoystickAxisV                   = 0x00000054,
    JoystickAxisHatX                = 0x00000064,
    JoystickAxisHatY                = 0x00000074,
    // Key codes                        
    KeyCodeUnknown                  = 0xFFFFFFF5,
    KeyCodeA                        = 0x00000005,
    KeyCodeB                        = 0x00000015,            
    KeyCodeC                        = 0x00000025,            
    KeyCodeD                        = 0x00000035,            
    KeyCodeE                        = 0x00000045,            
    KeyCodeF                        = 0x00000055,            
    KeyCodeG                        = 0x00000065,            
    KeyCodeH                        = 0x00000075,            
    KeyCodeI                        = 0x00000085,            
    KeyCodeJ                        = 0x00000095,            
    KeyCodeK                        = 0x000000A5,            
    KeyCodeL                        = 0x000000B5,            
    KeyCodeM                        = 0x000000C5,            
    KeyCodeN                        = 0x000000D5,            
    KeyCodeO                        = 0x000000E5,            
    KeyCodeP                        = 0x000000F5,            
    KeyCodeQ                        = 0x00000105,            
    KeyCodeR                        = 0x00000115,            
    KeyCodeS                        = 0x00000125,            
    KeyCodeT                        = 0x00000135,            
    KeyCodeU                        = 0x00000145,            
    KeyCodeV                        = 0x00000155,            
    KeyCodeW                        = 0x00000165,            
    KeyCodeX                        = 0x00000175,            
    KeyCodeY                        = 0x00000185,            
    KeyCodeZ                        = 0x00000195,          
    KeyCodeNum0                     = 0x000001A5,         
    KeyCodeNum1                     = 0x000001B5,         
    KeyCodeNum2                     = 0x000001C5,         
    KeyCodeNum3                     = 0x000001D5,         
    KeyCodeNum4                     = 0x000001E5,         
    KeyCodeNum5                     = 0x000001F5,         
    KeyCodeNum6                     = 0x00000205,         
    KeyCodeNum7                     = 0x00000215,         
    KeyCodeNum8                     = 0x00000225,         
    KeyCodeNum9                     = 0x00000235,         
    KeyCodeEscape                   = 0x00000245,
    KeyCodeLControl                 = 0x00000255,
    KeyCodeLShift                   = 0x00000265,
    KeyCodeLAlt                     = 0x00000275,
    KeyCodeLSystem                  = 0x00000285,
    KeyCodeRControl                 = 0x00000295,
    KeyCodeRShift                   = 0x000002A5,
    KeyCodeRAlt                     = 0x000002B5,
    KeyCodeRSystem                  = 0x000002C5,
    KeyCodeMenu                     = 0x000002D5,
    KeyCodeLBracket                 = 0x000002E5,
    KeyCodeRBracket                 = 0x000002F5,
    KeyCodeSemicolon                = 0x00000305,
    KeyCodeComma                    = 0x00000315,
    KeyCodePeriod                   = 0x00000325,
    KeyCodeApostrophe               = 0x00000335,
    KeyCodeSlash                    = 0x00000345,
    KeyCodeBackslash                = 0x00000355,
    KeyCodeGrave                    = 0x00000365,
    KeyCodeEqual                    = 0x00000375,
    KeyCodeHyphen                   = 0x00000385,
    KeyCodeSpace                    = 0x00000395,
    KeyCodeEnter                    = 0x000003A5,
    KeyCodeBackspace                = 0x000003B5,
    KeyCodeTab                      = 0x000003C5,
    KeyCodePageUp                   = 0x000003D5,
    KeyCodePageDown                 = 0x000003E5,
    KeyCodeEnd                      = 0x000003F5,
    KeyCodeHome                     = 0x00000405,
    KeyCodeInsert                   = 0x00000415,
    KeyCodeDelete                   = 0x00000425,
    KeyCodeAdd                      = 0x00000435,
    KeyCodeSubtract                 = 0x00000445,
    KeyCodeMultiply                 = 0x00000455,
    KeyCodeDivide                   = 0x00000465,
    KeyCodeLeft                     = 0x00000475,
    KeyCodeRight                    = 0x00000485,
    KeyCodeUp                       = 0x00000495,
    KeyCodeDown                     = 0x000004A5,
    KeyCodeNumpad0                  = 0x000004B5,      
    KeyCodeNumpad1                  = 0x000004C5,      
    KeyCodeNumpad2                  = 0x000004D5,      
    KeyCodeNumpad3                  = 0x000004E5,      
    KeyCodeNumpad4                  = 0x000004F5,      
    KeyCodeNumpad5                  = 0x00000505,      
    KeyCodeNumpad6                  = 0x00000515,      
    KeyCodeNumpad7                  = 0x00000525,      
    KeyCodeNumpad8                  = 0x00000535,      
    KeyCodeNumpad9                  = 0x00000545,      
    KeyCodeF1                       = 0x00000555,           
    KeyCodeF2                       = 0x00000565,           
    KeyCodeF3                       = 0x00000575,           
    KeyCodeF4                       = 0x00000585,           
    KeyCodeF5                       = 0x00000595,           
    KeyCodeF6                       = 0x000005A5,           
    KeyCodeF7                       = 0x000005B5,           
    KeyCodeF8                       = 0x000005C5,           
    KeyCodeF9                       = 0x000005D5,           
    KeyCodeF10                      = 0x000005E5,          
    KeyCodeF11                      = 0x000005F5,          
    KeyCodeF12                      = 0x00000605,          
    KeyCodeF13                      = 0x00000615,          
    KeyCodeF14                      = 0x00000625,          
    KeyCodeF15                      = 0x00000635,          
    KeyCodePause                    = 0x00000645        
    )
#pragma endregion InputCode

    /*                                 
    KeyScanUnknown                  = 0x000F04,
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
    KeyScanLaunchMediaSelect        = 0x000814


   */

}

struct InputValue
{
public:
  InputValue() = default;

  ~InputValue() = default;
  
  const Input::eINPUTSTATE& GetState()
  {
    return m_state;
  }

  void UpdateState(const Input::eINPUTSTATE& newValue)
  {
    m_state = newValue;
  }

  void* ReadRaw()
  {
    return &m_value;
  }
  
  const float& ReadValue()
  {
    return m_value;
  }

  void UpdateValue(const float& newValue)
  {
    m_value = newValue;
  }

  Input::eINPUTSTATE m_state = Input::eINPUTSTATE::INACTIVE;

  float m_timePressed;

  float m_timeInactive;

  float m_value;
};



