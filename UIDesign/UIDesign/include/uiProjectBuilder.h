#pragma once

#include "uiPrerequisites.h"
#include "uiModule.h"
#include "uiWindow.h"
#include "uiTexture.h"

class Scene;

struct ProjectSettings
{
  Map<uint32, Scene*> m_cookableScenes;
  Vector<VideoMode*> m_resolutions;
  String m_projectDir;
  String m_projectName;
  Texture* m_projectIcon;
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

