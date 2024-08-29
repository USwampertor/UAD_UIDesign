#pragma once

#include "uiUtilities.h"

enum eRESOURCETYPE : uint32
{
  NONE = 0,
  TEXTURE,
  SOUND,
  ANIMATION,
};

class Resource
{
  static eRESOURCETYPE GetType() { assert(true && "IMPLEMENT THIS"); return (eRESOURCETYPE::NONE); }
  virtual SizeT GetHashID() const = 0;
};