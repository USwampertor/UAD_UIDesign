#pragma once

#include "uiUtilities.h"
#include "uiResource.h"
#include "uiTexture.h"

#include <SFML/Graphics.hpp>

struct Frame
{
  sf::Sprite sprite;
  float interval;
};

class Animation : public Resource
{
public:
  Animation() = default;
  
  ~Animation() = default;

  static eRESOURCETYPE GetType() { return eRESOURCETYPE::ANIMATION; }

  void Initialize(Vector<SharedPtr<Texture>> newTextures, const float& duration);

  // void Update(const float& delta);

  void AddFrame(SharedPtr<Texture> newFrame);

  // void SetCurrentTime(const float& newValue);

  void SetLoop(const bool& ifLoop);

  SharedPtr<Texture> GetCurrentFrame(const float& currentTime);

public:

  float m_animationTime;

  Vector<SharedPtr<Texture>> m_frames;

  bool m_loop;

};

