#pragma once

#include "uiPrerequisites.h"

#include "uiResource.h"
#include "uiAudioBuffer.h"

class AudioClip : public Resource, public AudioBuffer 
{
public:
  AudioClip() : Resource(AudioClip::StaticType()) {}
  static eRESOURCETYPE StaticType() { return eRESOURCETYPE::SOUND; }
};

