#include "uiPawn.h"

#include "uiController.h"
#include "uiSceneManager.h"

void PawnEntity::AutoPossess()
{

}

JSONDocument PawnEntity::Serialize()
{
  JSONDocument d = Entity::Serialize();
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