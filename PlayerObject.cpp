#include "PlayerObject.h"

PlayerObject::PlayerObject(std::string tag, const char* name, Transform2Utility transform, float health, float maxHealth, float damage, float speed, float maxJump, const char* sprite) 
{
    m_Tag = tag;    
    m_Transform = &transform;

    // CHARACTER COMPONENT INIT
    m_Character = new CharacterComponent();
    m_Character->SetTransform(&transform);
    m_Character->SetName(name);
    m_Character->SetHealth(health);
    m_Character->SetMaxHealth(maxHealth);
    m_Character->SetDamage(damage);
    m_Character->SetSpeed(speed);
    m_Character->SetMaxJumps(maxJump);

    AddComponent(m_Character);

    // RENDER COMPONENT INIT
    m_Render = new RenderComponent();
    m_Render->SetTransform(&transform);
    m_Render->SetTextureSingleImage(sprite);

    AddComponent(m_Render);

    // ANIMATION COMPONENT INIT
    m_Animation = new AnimationComponent(m_Render);
    m_Animation->SetTransform(&transform);

    AddComponent(m_Animation);

    // COLLISION COMPONENT INIT
    m_Collision = new CollisionComponent();
    m_Collision->SetTransform(&transform);

    AddComponent(m_Collision);

    // INPUT COMPONENT INIT
    m_Input = new InputComponent();

    void Jump(); { m_Transform->position.y -= 10; }
    void MoveLeft(); { m_Transform->position.x += m_Character->GetSpeed(); }
    void MoveRight(); { m_Transform->position.x -= m_Character->GetSpeed(); }

    m_Input->SetKeyInput(InputType::INPUT_KEY_PRESS, KEY_SPACE, Jump);
    m_Input->SetKeyInput(InputType::INPUT_KEY_DOWN, KEY_A, MoveLeft);
    m_Input->SetKeyInput(InputType::INPUT_KEY_DOWN, KEY_D, MoveRight);

    AddComponent(m_Input);

    // PHYSICS COMPONENT INIT
    m_Physics = new PhysicsComponent(m_Collision);
    m_Physics->SetTransform(&transform);
    
    AddComponent(m_Physics);

}

PlayerObject::~PlayerObject() 
{
    if (m_Animation != nullptr) { m_Animation = nullptr; delete m_Animation; }
    if (m_Character != nullptr) { m_Character = nullptr; delete m_Character; }
    if (m_Collision != nullptr) { m_Collision = nullptr; delete m_Collision; }
    if (m_Input != nullptr) { m_Input = nullptr; delete m_Input; }
    if (m_Physics != nullptr) { m_Physics = nullptr; delete m_Physics; }
    if (m_Render != nullptr) { m_Render = nullptr; delete m_Render; }
}

void PlayerObject::Update(float DeltaTime) 
{
    GameObject::Update(DeltaTime);
}

void PlayerObject::Draw() 
{
    GameObject::Draw();
}

