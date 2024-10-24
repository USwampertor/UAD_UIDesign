#pragma once

#include "uiPrerequisites.h"

BETTER_ENUM(eRESOURCETYPE,
            uint32,
            NONE = 0,
            TEXTURE,
            SOUND,
            MUSIC,
            ANIMATION,
            ATLAS,
            FONT,
            SCENE
            )


class Resource
{
public:
  Resource(const eRESOURCETYPE& type) : m_type(type) {}
  static eRESOURCETYPE StaticType() { assert(true && "IMPLEMENT THIS"); return (eRESOURCETYPE::NONE); }
  const eRESOURCETYPE& GetType() { return m_type; }
  String m_resName = "";
private:
  eRESOURCETYPE m_type = eRESOURCETYPE::NONE;
};

