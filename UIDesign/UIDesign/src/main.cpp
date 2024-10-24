
#include "uiApp.h"
#include "uiFileSystem.h"
#include <iostream>
String FileSystem::m_exePath;
int main(int argc, char* argv[]) 
{
  // TODO: Check if there is a better way of doing this
  FileSystem::m_exePath = argv[0];
  App::StartUp(argc, argv);
  App::Instance().Run();

  return 0;

  
}