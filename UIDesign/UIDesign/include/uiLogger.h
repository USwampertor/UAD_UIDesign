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

struct Log
{
  Log(const String& message, const eLOGLEVEL& warningLevel = eLOGLEVEL::DEFAULT)
  : m_message(message),
    m_warningLevel(warningLevel) {}

  String m_message;
  eLOGLEVEL m_warningLevel;
};

class Logger : public Module<Logger>
{
  void AddLog(const String& message, const eLOGLEVEL& warningLevel = eLOGLEVEL::DEFAULT);

  void ToConsole(const String& message, const eLOGLEVEL& warningLevel = eLOGLEVEL::DEFAULT);

  void ToScreen(const String& message, const eLOGLEVEL& warningLevel = eLOGLEVEL::DEFAULT);
private:
  Map<uint32, Vector<UniquePtr<Log>>> m_logs;
};

