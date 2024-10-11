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
  String m_projectName;
  Texture* m_icon;
  void Serialize();
};

class ProjectBuilder : public Module<ProjectBuilder>
{
public:
  void BuildProject();
  ProjectSettings m_settings;
};

