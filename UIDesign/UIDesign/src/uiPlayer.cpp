#include "uiPlayer.h"


#include "uiAnimator.h"
#include "uiAudioClip.h"
#include "uiAudioListener.h"
#include "uiAudioSource.h"
#include "uiBoxCollider.h"
#include "uiCameraFollower.h"
#include "uiInput.h"
#include "uiInputAction.h"
#include "uiInputManager.h"
#include "uiMath.h"
#include "uiPhysics.h"
#include "uiResourceManager.h"
#include "uiSceneManager.h"
#include "uiSprite.h"

void PlayerEntity::Initialize()
{
  Entity::Initialize();
  
  m_maxHp = 3;
  m_hp = m_maxHp;
  m_onHPZero = std::bind(&PlayerEntity::OnPlayerDeath, this);
  
  m_animator = CreateComponent<Animator>();
  m_animator->AddAnimation(ResourceManager::Instance().GetResource<Animation>("idlePlayer"), "idle");
  m_animator->AddAnimation(ResourceManager::Instance().GetResource<Animation>("walkingPlayer"), "walking");
  m_animator->SetAnimation("idle");
  m_animator->Play();

  m_listener = CreateComponent<AudioListener>();
  
  m_source = CreateComponent<AudioSource>();
  m_source->SetClip(ResourceManager::Instance().GetResource<AudioClip>("pingas"));
  
  m_collider = CreateComponent<BoxCollider>();
  m_collider->setLayer(0, 1);
  m_collider->setLayer(1, 1);
  m_collider->m_parent = this;
  m_collider->setStatic(true);
  m_collider->SetSize(Vector2f(m_animator->GetSprite().getTexture()->getSize().x,
                               m_animator->GetSprite().getTexture()->getSize().y));

  m_map = MakeSharedObject<InputMapping>();
  m_map->BindAction(Input::eINPUTCODE::KeyCodeW, std::bind(&PlayerEntity::Up, this, std::placeholders::_1));
  m_map->BindAction(Input::eINPUTCODE::KeyCodeA, std::bind(&PlayerEntity::Left, this, std::placeholders::_1));
  m_map->BindAction(Input::eINPUTCODE::KeyCodeS, std::bind(&PlayerEntity::Down, this, std::placeholders::_1));
  m_map->BindAction(Input::eINPUTCODE::KeyCodeD, std::bind(&PlayerEntity::Right, this, std::placeholders::_1));
  m_map->BindAction(Input::eINPUTCODE::KeyCodeEnter, std::bind(&PlayerEntity::PlaySound, this, std::placeholders::_1));
  m_map->m_enabled = true;

  InputManager::Instance().RegisterInputMapping(m_map);
}

JSONDocument PlayerEntity::Serialize()
{
  JSONDocument d = CreatureEntity::Serialize();
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

void PlayerEntity::GetDamage(const float& damage)
{
  CreatureEntity::GetDamage(damage);
  m_animator->GetSprite().setColor(sf::Color(255, 128, 128, 128));
  m_damageTimer = 1;
}

void PlayerEntity::OnPlayerDeath()
{
  SceneManager::Instance().FindObject<CameraFollowerEntity>("Follower")->m_source->PlayOnce();
  SceneManager::Instance().DestroyObject(this);
}

void PlayerEntity::Update(const float& delta)
{
  Entity::Update(delta);

  if (m_damageTimer > 0)

  {
    m_damageTimer -= (delta * 0.001f);
    if (m_damageTimer < 0.01f) { m_damageTimer = 0.0f; }
    float ratio = (1 - m_damageTimer) / 1;
    float colorValue = Math::Lerp(128.0f, 255.0f, ratio);
    m_animator->GetSprite().setColor(sf::Color(255, colorValue, colorValue, colorValue));

  }

  Move(m_direction * delta * m_speed * 0.01f);
  if ((m_direction.x != 0 || m_direction.y != 0) && m_animator->m_animationName.compare("walking") != 0)
  {
    m_animator->Stop();
    m_animator->SetAnimation("walking");
    m_animator->Play();
  }
  else if (m_direction.x == 0 && m_direction.y == 0 && m_animator->m_animationName.compare("idle") != 0)
  {
    m_animator->Stop();
    m_animator->SetAnimation("idle");
    m_animator->Play();
  }
}

void PlayerEntity::Up(SharedPtr<InputValue> value)
{
  if (value->GetState() == Input::eINPUTSTATE::PRESSED ||
    value->GetState() == Input::eINPUTSTATE::HELD)
  {
    m_direction.y = -1;
  }
  else if (value->GetState() == Input::eINPUTSTATE::RELEASED)
  {
    m_direction.y = 0;
  }
}

void PlayerEntity::Down(SharedPtr<InputValue> value)
{
  if (value->GetState() == Input::eINPUTSTATE::PRESSED ||
    value->GetState() == Input::eINPUTSTATE::HELD)
  {
    m_direction.y = 1;
  }
  else if (value->GetState() == Input::eINPUTSTATE::RELEASED)
    // else
  {
    m_direction.y = 0;
  }
}

void PlayerEntity::Left(SharedPtr<InputValue> value)
{
  if (value->GetState() == Input::eINPUTSTATE::PRESSED ||
    value->GetState() == Input::eINPUTSTATE::HELD)
  {
    m_direction.x = -1;
    m_animator->GetSprite().FlipX(false);
  }
  else if (value->GetState() == Input::eINPUTSTATE::RELEASED)
    // else
  {
    m_direction.x = 0;
  }
}

void PlayerEntity::Right(SharedPtr<InputValue> value)
{
  if (value->GetState() == Input::eINPUTSTATE::PRESSED ||
    value->GetState() == Input::eINPUTSTATE::HELD)
  {
    m_direction.x = 1;
    m_animator->GetSprite().FlipX(true);

  }
  else if (value->GetState() == Input::eINPUTSTATE::RELEASED)
  {
    m_direction.x = 0;
  }
}

void PlayerEntity::PlaySound(SharedPtr<InputValue> value)
{
  if (value->GetState() == Input::eINPUTSTATE::PRESSED)
  {
    m_source->PlayOnce();
  }
}

void PlayerEntity::EnterCollision(const PhysicsCollisionResult& c)
{

}

void PlayerEntity::StayCollision(const PhysicsCollisionResult& c)
{

}

void PlayerEntity::ExitCollision(const PhysicsCollisionResult& c)
{

}
