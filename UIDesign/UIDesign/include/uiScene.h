
#pragma once

#include "uiUtilities.h"
#include "uiEntity.h"

class Scene
{
public:

  void Initialize()
  {
    m_root = MakeUniqueObject<Entity>();
    m_root->Initialize();
  }

  UniquePtr<Entity> m_root;

  

};

