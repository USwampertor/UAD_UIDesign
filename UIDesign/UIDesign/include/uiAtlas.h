#pragma once

#include "uiPrerequisites.h"

#include "uiResource.h"
#include "uiTexture.h"

class Atlas : public Resource
{
public:

  Atlas() : Resource(Atlas::StaticType()) {}
  ~Atlas() = default;

  static eRESOURCETYPE StaticType() { return eRESOURCETYPE::ATLAS; }

  Vector<SharedPtr<Texture>> m_atlas;
};
