#pragma once

#include "uiPrerequisites.h"

#include "uiResource.h"
#include "uiTexture.h"
#include "uiUtilities.h"

class Animation : public Resource
{
public:
  Animation() = default;
  
  ~Animation() = default;

  static eRESOURCETYPE GetType() { return eRESOURCETYPE::ANIMATION; }

  void Initialize(Vector<SharedPtr<Texture>> newTextures, const float& duration);

  void AddFrame(SharedPtr<Texture> newFrame);

  void SetLoop(const bool& ifLoop);

  SharedPtr<Texture> GetCurrentFrame(const float& currentTime);

public:

  float m_animationTime;

  Vector<SharedPtr<Texture>> m_frames;

  bool m_loop;

};

