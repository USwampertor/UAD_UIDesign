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
            FONT
            )


class Resource
{
public:
  static eRESOURCETYPE GetType() { assert(true && "IMPLEMENT THIS"); return (eRESOURCETYPE::NONE); }
  // virtual JSONDocument Serialize() = 0;
};

