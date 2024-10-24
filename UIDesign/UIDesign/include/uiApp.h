#pragma once

#include "uiPrerequisites.h"

#include "uiModule.h"
#include "uiArgumentParser.h"
#include "uiProjectBuilder.h"
#include "uiSplashScreen.h"


class App : public Module<App>
{
public:

  App() = default;

  App(const String& params)
  {
    m_parser.Parse(params);
  }

  App(int argc, char* argv[])
  {
    m_parser.Parse(argc, argv);
  }

  virtual void OnStartUp() override;

  bool StartSystems();

  bool LoadResources();

  void Run();

  void Exit();

  void Update();

  SplashScreen m_splashScreen;
  ArgumentParser m_parser;

#if UI_EDITOR_MODE
  UniquePtr<ProjectBuilder> m_projectBuilder;
#endif


};

