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


class Component
{
public:

  Component()
  {
    m_offset = MakeUniqueObject<Transform2D>();
  }

  static String GetType() { assert(true && "IMPLEMENT THIS"); return "Component"; }

  virtual void Initialize() = 0;

  virtual void PropagateTransform(const Transform2D& newTransform) = 0;
  
  virtual void Update(const float& delta) = 0;

  Transform2D& GetOffset()
  {
    return *m_offset;
  }

  void SetOffset(const Transform2D& offset)
  {
    m_offset->SetTransform(offset);
  }

protected:
  SharedPtr<Entity> m_parent;

  UniquePtr<Transform2D> m_offset;
};
