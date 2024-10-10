#include "uiArgumentParser.h"

void ArgumentParser::Parse(const String& params)
{
  for (auto argument : m_argumentMap)
  {

  }
}


void ArgumentParser::AddFlag(const String& param)
{
  if (m_argumentMap.find(param) == m_argumentMap.end())
  {
    m_argumentMap.insert(Utils::MakePair(param, ""));
  }
}

void ArgumentParser::SetFlag(const String& param, const String& newValue)
{
  if (m_argumentMap.find(param) != m_argumentMap.end())
  {
    m_argumentMap[param] = newValue;
  }
}

const String& ArgumentParser::GetFlag(const String& param)
{
  if (m_argumentMap.find(param) != m_argumentMap.end())
  {
    return m_argumentMap[param];
  }
  return m_argumentMap["NONE"];
}

