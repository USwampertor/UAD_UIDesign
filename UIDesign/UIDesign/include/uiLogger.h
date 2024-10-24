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
  DEFAULT = 0,
  SPLASH,
  DEBUGGER,
  SCREEN
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

  void AddLoggerCallback(const LoggerCallback& c);

  void OnLogAdded(const Log& newLog);

  void Dump();

private:
  Vector<UniquePtr<Log>> m_logs;

  Vector<LoggerCallback> m_callbacks;

};

