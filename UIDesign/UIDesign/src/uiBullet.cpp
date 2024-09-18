#include "uiBullet.h"

#include "uiSceneManager.h"

void BulletEntity::EnterCollision(const PhysicsCollisionResult& c)
{
  std::cout << "Entered Collision" << std::endl;
  --m_life;
  if (m_life <= 0)
  {
    SceneManager::Instance().DestroyObject(this);
  }
}