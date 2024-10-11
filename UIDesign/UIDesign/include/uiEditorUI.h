#pragma once
#include "uiPrerequisites.h"

class EditorUI
{
public:

  void Initialize();

  void DrawUI();
  
  Map<String, bool> m_windowVisibilities;
};

