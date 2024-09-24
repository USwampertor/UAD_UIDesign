#include "uiBullet.h"

#include "uiPlayer.h"
#include "uiSceneManager.h"

void BulletEntity::EnterCollision(const PhysicsCollisionResult& c)
{
  std::cout << "Entered Collision" << std::endl;
  Entity* player = reinterpret_cast<BoxCollider*>(&c.object2)->m_parent;
  if (player->GetName() == "Player")
  {
    // reinterpret_cast<PlayerEntity*>(player)->GetDamage(1);
    // SceneManager::Instance().DestroyObject(this);
  }
}