#include "uiArgumentParser.h"

void ArgumentParser::Parse(int argc, char* argv[])
{
  String currentFlag;

  for (int i = 1; i < argc; ++i) {
    String token = argv[i];

    if (token[0] == '-') {  // If the token is a flag
      currentFlag = token.substr(1);  // Remove the leading '-'
      AddFlag(currentFlag);  // Initialize with an empty vector
    }
    else if (!currentFlag.empty()) {
      SetFlag(currentFlag, token);  // Store value under current flag
    }
  }
}

void ArgumentParser::Parse(const String& params)
{
  SStream stream(params);
  String token;
  String currentFlag;
  // Regex tokenRegex("((-[\w-]+)|\"([^\"]*)\" | (\S + ))");

  while (stream >> token)
  {
    if (token[0] == '-') 
    {
      currentFlag = token.substr(1);
      AddFlag(currentFlag);
    }
    else if (!currentFlag.empty())
    {
      SetFlag(currentFlag, token);
    }
  }

}


void ArgumentParser::AddFlag(const String& param)
{
  if (m_argumentMap.find(param) == m_argumentMap.end())
  {
    m_argumentMap[param] = {};
  }
}

void ArgumentParser::SetFlag(const String& param, const String& newValue)
{
  if (m_argumentMap.find(param) != m_argumentMap.end())
  {
    m_argumentMap[param].push_back(newValue);
  }
}

const Vector<String>& ArgumentParser::GetFlag(const String& param)
{
  if (m_argumentMap.find(param) != m_argumentMap.end())
  {
    return m_argumentMap[param];
  }
  return {};
}

bool ArgumentParser::HasFlag(const String& flag)
{
  return m_argumentMap.find(flag) != m_argumentMap.end();
}
