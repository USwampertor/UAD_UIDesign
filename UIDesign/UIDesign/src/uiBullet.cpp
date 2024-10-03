#include "uiBullet.h"

#include "uiPlayer.h"
#include "uiSceneManager.h"

void BulletEntity::Initialize()
{
  Entity::Initialize();
  
  m_animator = CreateComponent<Animator>();
  m_animator->AddAnimation(ResourceManager::Instance().GetResource<Animation>("idleBullet"), "idle");
  m_animator->SetAnimation("idle");
  m_animator->Play();
  
  m_collider = CreateComponent<BoxCollider>();
  m_collider->setStatic(false);
  m_collider->setTrigger(true);
  m_collider->SetSize(Vector2f(m_animator->GetSprite().getTexture()->getSize().x,
                               m_animator->GetSprite().getTexture()->getSize().y));
  SetScale(Vector2f(0.25f, 0.25f));

  m_collider->AddCollisionEnterCallback(std::bind(&BulletEntity::EnterCollision, this, std::placeholders::_1));
}

void BulletEntity::EnterCollision(const PhysicsCollisionResult& c)
{
  BoxCollider* collider = static_cast<BoxCollider*>(&c.object2);
  if (collider->m_parent->GetName() == "Player")
  {
    static_cast<PlayerEntity*>(collider->m_parent)->GetDamage(1);
    SceneManager::Instance().DestroyObject(this);
  }
}