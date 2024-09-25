#pragma once
#include "uiUtilities.h"

class Entity;

struct Transform2D
{
public:
  Transform2D()
  {
    Reset();
  }

  Transform2D(const Vector2f& p, const Vector2f& s, const float& r)
  {
    SetTransform(p, s, r);
  }

  ~Transform2D() = default;

  void SetTransform(const Vector2f& p, const Vector2f& s, const float& r)
  {
    position = p;
    scale = s;
    rotation = r;
  }

  void SetTransform(const Transform2D& t)
  {
    SetTransform(t.position, t.scale, t.rotation);
  }


  void Reset()
  {
    position = { 0,0 };
    scale = { 1,1 };
    rotation = 0;
  }

  Vector2f position;

  Vector2f scale;
  
  float rotation;
};

BETTER_ENUM(
  eCOMPONENTTYPE,
  uint32,
  NONE            = 0,
  ANIMATOR        = 1 << 0,
  AUDIOLISTENER   = 1 << 1,
  AUDIOSOURCE     = 1 << 2,
  CAMERA          = 1 << 3,
  COLLIDER        = 1 << 4,
  PARTICLEEMITTER = 1 << 5,
  SPRITE          = 1 << 6
)


class Component
{
public:

  Component()
  {
    m_offset = MakeUniqueObject<Transform2D>();
  }

  static eCOMPONENTTYPE GetType() { assert(true && "IMPLEMENT THIS"); return eCOMPONENTTYPE::NONE; }

  virtual void Initialize() = 0;

  virtual void OnDestroy() = 0;

  virtual void PropagateTransform(const Transform2D& newTransform) = 0;
  
  virtual void Update(const float& delta) = 0;

  Transform2D& GetOffset()
  {
    return *m_offset;
  }

  void SetOffset(const Transform2D& offset)
  {
    m_offset->SetTransform(offset);
    OnSetOffset();
  }

  virtual void OnSetOffset() {}

  Entity* m_parent = nullptr;
protected:

  UniquePtr<Transform2D> m_offset;
};
