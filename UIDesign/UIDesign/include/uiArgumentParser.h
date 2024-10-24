#pragma once

#include "uiPrerequisites.h"
#include "uiUtilities.h"

class ArgumentParser
{
public:

  ArgumentParser()
  {

  }

  ~ArgumentParser() = default;

  void Parse(int argc, char* argv[]);

  void Parse(const String& params);

  void AddFlag(const String& param);

  void SetFlag(const String& param, const String& newValue);

  const Vector<String>& GetFlag(const String& flag);

  bool HasFlag(const String& flag);

  Map<String, Vector<String>> m_argumentMap;
};

