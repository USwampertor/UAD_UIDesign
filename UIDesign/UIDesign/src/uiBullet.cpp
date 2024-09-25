#include "uiBullet.h"

#include "uiPlayer.h"
#include "uiSceneManager.h"

void BulletEntity::EnterCollision(const PhysicsCollisionResult& c)
{
  std::cout << "Entered Collision" << std::endl;
  BoxCollider* collider = static_cast<BoxCollider*>(&c.object2);
  if (collider->m_parent->GetName() == "Player")
  {
    static_cast<PlayerEntity*>(collider->m_parent)->GetDamage(1);
    SceneManager::Instance().DestroyObject(this);
  }
}