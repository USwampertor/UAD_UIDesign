#pragma once

#include "uiPrerequisites.h"
#include "uiUtilities.h"

class ArgumentParser
{
public:

  ArgumentParser()
  {
    m_argumentMap.insert(Utils::MakePair("NONE", "NONE"));
  }

  ~ArgumentParser() = default;

  void Parse(const String& params);

  void AddFlag(const String& param);

  void SetFlag(const String& param, const String& newValue);

  const String& GetFlag(const String& param);

  Map<String, String> m_argumentMap;
};

