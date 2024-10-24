#pragma once
#include "uiPrerequisites.h"
#include "uiVector2.h"
// #include "uiLogger.h"

class Log;
class Entity;


struct BrowserThumbnail
{
  uint32 id;
  String path;
};

struct AssetBrowser
{
  float m_iconSize = 32;
  uint32 m_iconSpacing = 10;
  uint32 m_iconHitSpacing = 4;
  bool m_stretchSpacing = true;

  Vector<BrowserThumbnail> m_items;
  // ImGuiSelectionBasicStorage m_selection;
  uint32 m_nextItemID;

  Vector2f m_layoutItemSize;
  Vector2f m_layoutItemStep;

  float           m_layoutItemSpacing = 0.0f;
  float           m_layoutSelectableSpacing = 0.0f;
  float           m_layoutOuterPadding = 0.0f;
  uint32          m_layoutColumnCount = 0;
  uint32          m_layoutLineCount = 0;


  void Clear()
  {
    m_items.clear();
    // m_selection.Clear();
  }
};

class EditorUI
{
public:

  void Initialize();

  void DrawUI();

  void AddDebuggerLog(const Log& newLog);
  
  Map<String, bool> m_windowVisibilities;

  Vector<const Log*> m_debugLogs;

  Vector<Entity*> m_selectedEntity;
};

