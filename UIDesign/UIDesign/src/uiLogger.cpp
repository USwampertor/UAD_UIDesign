#include "uiLogger.h"

#include "uiFileSystem.h"
#include "uiUtilities.h"

#include <iostream>

void Logger::AddLog(const String& message, 
                    const eLOGLEVEL& warningLevel,
                    const eLOGFLAG& flag)
{
  m_logs.push_back(MakeUniqueObject<Log>(message, warningLevel, flag));
  OnLogAdded(*m_logs.back());
}

void Logger::OnLogAdded(const Log& newLog)
{
  for(auto& c : m_callbacks)
  {
    c(newLog);
  }
}

void Logger::AddOnLogAddedCallback(const LoggerCallback& c)
{
  m_callbacks.push_back(c);
}

void Logger::Dump()
{
  Path p(Utils::Format("%s/%s", 
                       FileSystem::WorkingPath().string().c_str(), 
                       "logDump.txt"));

  OFStream output(p.string().c_str());
  if (!output)
  {
    return;
  }

  for (const auto& log : m_logs)
  {
    output << log->m_message << std::endl;
  }

}

void Logger::ToSplashScreen(const String& message, const eLOGLEVEL& warningLevel)
{
  AddLog(message, warningLevel, eLOGFLAG::SPLASH);
}

void Logger::ToDebugger(const String& message, const eLOGLEVEL& warningLevel)
{
  AddLog(message, warningLevel, eLOGFLAG::DEBUGGER);
}

void Logger::ToConsole(const String& message, const eLOGLEVEL& warningLevel)
{
  AddLog(message, warningLevel, eLOGFLAG::CONSOLE);
  std::cout << message << std::endl;
}

void Logger::ToScreen(const String& message, const eLOGLEVEL& warningLevel)
{
  AddLog(message, warningLevel, eLOGFLAG::SCREEN);
}

