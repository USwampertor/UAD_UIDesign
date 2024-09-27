#include "uiEnemy.h"


#include "uiBoid.h"
#include "uiBoxCollider.h"
#include "uiMath.h"
#include "uiSceneManager.h"
#include "uiBullet.h"
#include "uiMath.h"


#include "imgui.h"
#include "imgui-SFML.h"

void EnemyEntity::OnEnemyDeath()
{
  // SceneManager::Instance().DestroyObject(this);
}

void EnemyEntity::Update(const float& delta)
{
  Entity::Update(delta);
  m_timeBeforeSpawn -= (delta / 1000);
  Entity* player = SceneManager::Instance().FindObject<Entity>("Player");
  // ImGui::Begin(GetName().c_str());
  // ImGui::Text(Utils::Format("%f , %f",GetTransform().position.x, GetTransform().position.y).c_str());
  // ImGui::Text(Utils::Format("%f , %f", GetComponent<AudioSource>()->m_sound->getPosition().x, 
  //                                       GetComponent<AudioSource>()->m_sound->getPosition().y).c_str());
  // 
  // ImGui::End();
  Vector2f direction = Boid::Approach(this->GetTransform().position, player->GetTransform().position, 5, 50) * (delta / 1000);
  if (m_timeBeforeSpawn <= 0)
  {
    GetComponent<AudioSource>()->Play();
    BulletEntity* bullet = SceneManager::Instance().CreateObject<BulletEntity>("bullet");
    bullet->SetPosition(this->GetTransform().position);
    bullet->GetComponent<BoxCollider>()->setStatic(false);
    bullet->GetComponent<BoxCollider>()->setLayer(1, 1);
    bullet->GetComponent<BoxCollider>()->setLayer(0, 0);
    bullet->GetComponent<BoxCollider>()->setVelocity(Vec2Math<float>::Times(direction, 2));
    // bullet->m_direction = Vec2Math<float>::Times(direction, 5);
    m_timeBeforeSpawn = std::rand() % 10 + 5;
  }
  // this->Move();
  this->GetComponent<BoxCollider>()->setVelocity(direction);
}