#pragma once

#include "uiPrerequisites.h"

#include "uiResource.h"
#include "uiTexture.h"

class Atlas : public Resource
{
public:

  Atlas() = default;
  ~Atlas() = default;

  static eRESOURCETYPE GetType() { return eRESOURCETYPE::ATLAS; }

  Vector<SharedPtr<Texture>> m_atlas;
};
