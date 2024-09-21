#pragma once

#include "uiPrerequisites.h"

#include "uiModule.h"

class App : public Module<App>
{
public:
  virtual void OnStartUp() override;

  bool StartSystems();

  bool LoadResources();

  void Run();

  void Exit();

  void Update();

};

