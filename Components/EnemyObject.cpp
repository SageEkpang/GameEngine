#include "EnemyObject.h"

EnemyObject::EnemyObject(std::string tag, const char* name, Transform2Utility transform, float health, float damage, float speed, float maxJump, const char* sprite) 
{
    m_Tag = tag;

    m_Transform = &transform;
    m_Character = new CharacterComponent();
    m_Character->SetName(name);
    m_Character->SetHealth(health);
    // m_Character->SetMaxHealth();
    m_Character->SetDamage(damage);
    m_Character->SetSpeed(speed);
    m_Character->SetMaxJumps(maxJump);

    AddComponent(m_Character);

    m_Collision = new CollisionComponent();
    m_Collision->SetTransform(&transform);

    AddComponent(m_Collision);

    m_Render = new RenderComponent();
    m_Render->SetTextureSingleImage(sprite);
    m_Render->SetTransform(&transform);

    AddComponent(m_Render);

    m_Physics = new PhysicsComponent(m_Collision);

    AddComponent(m_Physics);
}

EnemyObject::~EnemyObject() 
{
    // DELETE COMPONENT(s)
    // if (m_Animation != nullptr) { m_Animation = nullptr; delete m_Animation; }
    if (m_Character != nullptr) { m_Character = nullptr; delete m_Character; }
    if (m_Collision != nullptr) { m_Collision = nullptr; delete m_Collision; }
    if (m_Physics != nullptr) { m_Physics = nullptr; delete m_Physics; }
    if (m_Render != nullptr) { m_Render = nullptr; delete m_Render; }
}

void EnemyObject::Update(float DeltaTime) 
{
    GameObject::Update(DeltaTime);
}

void EnemyObject::Draw() 
{
    GameObject::Draw();
}

