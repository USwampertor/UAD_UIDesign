#include "uiLogger.h"

#include "uiFileSystem.h"
#include "uiUtilities.h"

#include <chrono>

void Logger::AddLog(const String& message, 
                    const eLOGLEVEL& warningLevel,
                    const eLOGFLAG& flag)
{
  m_logs.push_back(MakeUniqueObject<Log>(message, warningLevel, flag));
  OnLogAdded(*m_logs.back());
  std::this_thread::sleep_for(std::chrono::milliseconds(100));
}

void Logger::OnLogAdded(const Log& newLog)
{
  for(auto& c : m_callbacks)
  {
    c(newLog);
  }
}

void Logger::AddLoggerCallback(const LoggerCallback& c)
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

