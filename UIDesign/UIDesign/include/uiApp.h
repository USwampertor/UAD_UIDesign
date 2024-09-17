#pragma once

#include "uiPrerequisites.h"

#include "uiModule.h"
#include "uiResourceManager.h"

class App : public Module<App>
{
  virtual void OnStartUp() override
  {
    ResourceManager::StartUp();
  }

  void LoadResources()
  {

  }

  void Run()
  {
   
  }


};

