#pragma once

#include "uiPrerequisites.h"

#include "uiUtilities.h"

enum eRESOURCETYPE : uint32
{
  NONE = 0,
  TEXTURE,
  SOUND,
  MUSIC,
  ANIMATION,
  ATLAS,
};

class Resource
{
  static eRESOURCETYPE GetType() { assert(true && "IMPLEMENT THIS"); return (eRESOURCETYPE::NONE); }
};

