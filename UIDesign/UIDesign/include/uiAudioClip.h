#pragma once

#include "uiPrerequisites.h"

#include "uiResource.h"
#include "uiAudioBuffer.h"

class AudioClip : public Resource, public AudioBuffer 
{
public:
  static eRESOURCETYPE GetType() { return eRESOURCETYPE::SOUND; }
};

