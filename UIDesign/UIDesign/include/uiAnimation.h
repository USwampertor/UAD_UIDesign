#pragma once

#include "uiUtilities.h"
#include "uiResource.h"

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
  virtual SizeT GetHashID() const override {  };


  void AddFrame(sf::Texture* newFrame);

  void Initialize(Vector<sf::Texture*> newTextures, float duration);

  void Update(float delta);

  void SetCurrentTime(float newValue);

  void SetLoop(bool ifLoop);

  sf::Texture* GetCurrentFrame();

public:

  float m_currentTime;

  float m_animationTime;

  Vector<sf::Texture*> m_frames;

  bool m_loop;

};

