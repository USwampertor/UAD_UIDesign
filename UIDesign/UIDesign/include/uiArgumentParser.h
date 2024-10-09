#pragma once

#include "uiPrerequisites.h"
#include "uiUtilities.h"

class ArgumentParser
{
public:

  ArgumentParser()
  {
    m_argumentMap.insert(Utils::MakePair("NONE", ""));
  }

  ~ArgumentParser() = default;

  void Parse(const String& params);

  void AddArgument(const String& newArg);

  const String& GetParameter(const String& param);

  Map<String, String> m_argumentMap;
};

