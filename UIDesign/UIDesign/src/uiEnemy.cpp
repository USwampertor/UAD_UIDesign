#include "uiEnemy.h"

#include "uiAnimator.h"
#include "uiAudioSource.h"
#include "uiBoid.h"
#include "uiBoxCollider.h"
#include "uiMath.h"
#include "uiResourceManager.h"
#include "uiSceneManager.h"
#include "uiBullet.h"
#include "uiMath.h"
#include "uiPhysics.h"
#include "uiSprite.h"


#include "imgui.h"
#include "imgui-SFML.h"

void EnemyEntity::Initialize()
{
  Entity::Initialize();

  m_hp = m_maxHp;
  m_timeBeforeSpawn = std::rand() % 10 + 5;
  m_onHPZero = std::bind(&EnemyEntity::OnEnemyDeath, this);


  m_animator = CreateComponent<Animator>();
  m_animator->AddAnimation(ResourceManager::Instance().GetResource<Animation>("idleEnemy"), String("idle"));
  m_animator->SetAnimation("idle");
  m_animator->SetCurrentTime(std::rand() % 1000);
  m_animator->Play();


  m_collider = CreateComponent<BoxCollider>();
  m_collider->setStatic(false);
  m_collider->setMass(5);
  m_collider->setLayer(0, 1);
  m_collider->SetSize(Vector2f(m_animator->GetSprite().getTexture()->getSize().x,
                               m_animator->GetSprite().getTexture()->getSize().y));
  
  m_source = CreateComponent<AudioSource>();
  m_source->SetClip(ResourceManager::Instance().GetResource<AudioClip>("ping"));
  m_source->SetMinDistance(150);
  m_source->SetAttenuation(5);
  m_source->SetLoop(false);

  Move(Vector2f((std::rand() % 10000) - 5000, (std::rand() % 10000) - 5000));
}

void EnemyEntity::OnEnemyDeath()
{
  // SceneManager::Instance().DestroyObject(this);
}

void EnemyEntity::Update(const float& delta)
{
  Entity::Update(delta);
  m_timeBeforeSpawn -= (delta / 1000);
  Entity* player = SceneManager::Instance().FindObject<Entity>("Player");
  if (player != nullptr)
  {
    Vector2f direction = Boid::Approach(this->GetTransform().position, player->GetTransform().position, 5, 50) * (delta / 1000);

    GetComponent<Animator>()->GetSprite().FlipX(direction.x > 0 ? true : false);
    if (m_timeBeforeSpawn <= 0)
    {
      GetComponent<AudioSource>()->Play();
      BulletEntity* bullet = SceneManager::Instance().CreateObject<BulletEntity>("bullet");
      bullet->SetPosition(this->GetTransform().position);
      bullet->GetComponent<BoxCollider>()->setStatic(false);
      bullet->GetComponent<BoxCollider>()->setLayer(1, 1);
      bullet->GetComponent<BoxCollider>()->setLayer(0, 0);
      bullet->GetComponent<BoxCollider>()->setVelocity(Vec2Math<float>::Times(direction, 3));
      // bullet->m_direction = Vec2Math<float>::Times(direction, 5);
      m_timeBeforeSpawn = std::rand() % 10 + 5;
    }
    // this->Move();
    this->GetComponent<BoxCollider>()->setVelocity(direction);
  }
}