#pragma once

#include "uiPrerequisites.h"

#include "uiModule.h"

BETTER_ENUM(
  eLOGLEVEL,
  uint32,
  DEFAULT = 0,
  DEBUG,
  WARNING,
  ERROR
)

BETTER_ENUM(
  eLOGFLAG,
  uint32,
  DEFAULT   = 1 << 0,
  SPLASH    = 1 << 1,
  DEBUGGER  = 1 << 2,
  SCREEN    = 1 << 3,
  CONSOLE   = 1 << 4
)


struct Log
{
  Log(const String& message, 
      const eLOGLEVEL& warningLevel = eLOGLEVEL::DEFAULT, 
      const eLOGFLAG& flag = eLOGFLAG::DEFAULT)
  : m_message(message),
    m_warningLevel(warningLevel),
    m_flag(flag) {}

  String m_message;
  eLOGLEVEL m_warningLevel;
  eLOGFLAG m_flag;
};

using LoggerCallback = Callback<void, const Log&>;

class Logger : public Module<Logger>
{
public:
  void AddLog(const String& message, 
              const eLOGLEVEL& warningLevel = eLOGLEVEL::DEFAULT, 
              const eLOGFLAG& flag = eLOGFLAG::DEFAULT);

  void AddOnLogAddedCallback(const LoggerCallback& c);

  void OnLogAdded(const Log& newLog);

  void Dump();

  void ToSplashScreen(const String& message, const eLOGLEVEL& warningLevel = eLOGLEVEL::DEFAULT);

  void ToConsole(const String& message, const eLOGLEVEL& warningLevel = eLOGLEVEL::DEFAULT);

  void ToScreen(const String& message, const eLOGLEVEL& warningLevel = eLOGLEVEL::DEFAULT);

  void ToDebugger(const String& message, const eLOGLEVEL& warningLevel = eLOGLEVEL::DEFAULT);


private:
  Vector<UniquePtr<Log>> m_logs;

  Vector<LoggerCallback> m_callbacks;

};

