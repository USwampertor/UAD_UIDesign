#include "uiArgumentParser.h"

void ArgumentParser::Parse(const String& params)
{
  for (auto argument : m_argumentMap)
  {

  }
}


void ArgumentParser::AddArgument(const String& newArg)
{

}

const String& ArgumentParser::GetParameter(const String& param)
{
  if (m_argumentMap.find(param) != m_argumentMap.end())
  {
    return m_argumentMap[param];
  }
  return m_argumentMap["NONE"];
}

