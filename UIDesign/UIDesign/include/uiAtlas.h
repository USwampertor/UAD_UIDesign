#pragma once

#include "uiPrerequisites.h"

#include "uiResource.h"
#include "uiTexture.h"

// TODO: Change the way Atlases work. They should contain the whole sprite and the positions to cut
class Atlas : public Resource
{
public:

  Atlas() : Resource(Atlas::StaticType()) {}
  ~Atlas() = default;

  static eRESOURCETYPE StaticType() { return eRESOURCETYPE::ATLAS; }

  Vector<SharedPtr<Texture>> m_atlas;
};
