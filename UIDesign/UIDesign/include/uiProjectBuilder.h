#pragma once

#include "uiPrerequisites.h"

#include "uiAppSettings.h"
#include "uiModule.h"
#include "uiTexture.h"
#include "uiWindow.h"

class Scene;

struct ProjectSettings
{
  Map<uint32, Scene*> m_cookableScenes;
  Vector<VideoMode*> m_resolutions;
  String m_projectDir;
  String m_projectName;
  Texture* m_projectIcon;
  bool m_shouldUseVerticalSync = false;
  int32 m_framerate = 144;

  // TODO: Change this so project settings has app settings
  // AppSettings m_settings;
  void Serialize();
};

class ProjectBuilder
{
public:
  void Initialize();
  void BuildProject();
  void StartBuildingThread();
  ProjectSettings m_settings;
  String m_projectIconStr = "gizmo";
  float m_buildingPercentage;
  Thread* t;
};

