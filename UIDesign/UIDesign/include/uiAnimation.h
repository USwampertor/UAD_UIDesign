#pragma once

#include "uiPrerequisites.h"

#include "uiResource.h"
#include "uiTexture.h"
#include "uiUtilities.h"

class Animation : public Resource
{
public:
  Animation() : Resource(Animation::StaticType()) {}

  ~Animation() = default;

  static eRESOURCETYPE StaticType() { return eRESOURCETYPE::ANIMATION; }

  void Initialize(Vector<SharedPtr<Texture>> newTextures, const float& duration);

  void AddFrame(SharedPtr<Texture> newFrame);

  void SetLoop(const bool& ifLoop);

  SharedPtr<Texture> GetCurrentFrame(const float& currentTime);

public:

  float m_animationTime = 0.0f;

  Vector<SharedPtr<Texture>> m_frames;

  bool m_loop = false;

};

