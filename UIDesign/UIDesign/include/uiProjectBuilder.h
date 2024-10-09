#pragma once

#include "uiPrerequisites.h"
#include "uiModule.h"

class Scene;

struct ProjectSettings
{
  Map<uint32, Scene*> m_cookableScenes;

};

class ProjectBuilder : public Module<ProjectBuilder>
{
  void BuildProject();
  ProjectSettings m_settings;
};

