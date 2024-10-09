#include "uiProjectBuilder.h"

#include "uiScene.h"
#include "uiJSON.h"

void ProjectBuilder::BuildProject()
{
  JSONDocument gameDocument;

  // 

  // Creation of scenes in document
  for (int i = 0; i < m_settings.m_cookableScenes.size(); ++i)
  {
    m_settings.m_cookableScenes[i]->Serialize();
  }




}
