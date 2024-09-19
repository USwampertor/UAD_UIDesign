#include "uiEnemy.h"

#include "uiSceneManager.h"

void Enemy::OnEnemyDeath()
{
  SceneManager::Instance().DestroyObject(this);
}

