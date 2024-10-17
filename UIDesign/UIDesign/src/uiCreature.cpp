#include "uiCreature.h"


void CreatureEntity::GetDamage(const float& damage)
{
  m_hp -= damage;
  if (m_hp <= 0)
  {
    m_onHPZero();
  }
}

JSONDocument CreatureEntity::Serialize()
{
  JSONDocument d = PawnEntity::Serialize();
  JSONDocument::AllocatorType& allocator = d.GetAllocator();
  if (d.HasMember("type"))
  {
    d["type"].SetString(GetType().c_str(), allocator);
  }
  else
  {
    JSONValue v;
    v.SetString(GetType().c_str(), allocator);
    d.AddMember("type", v, allocator);
  }
  return d;
}

