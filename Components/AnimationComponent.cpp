#include "AnimationComponent.h"
#include "RenderComponent.h"

AnimationComponent::AnimationComponent(RenderComponent* renderComponent) 
{
    m_RenderComponent = new RenderComponent();
    m_RenderComponent = renderComponent;
}

AnimationComponent::~AnimationComponent() 
{
    if (m_RenderComponent != nullptr)
    {
        m_RenderComponent = nullptr;
        delete m_RenderComponent;
    }
}

void AnimationComponent::Update(float deltaTime) 
{
    // FLIP SPRITE
    if (m_FlipX == true) { m_Flip = -1; }
    else if (m_FlipX == false) { m_Flip = 1; }

    // ANIMATE SPRITE SHEET
    m_RunningTime += deltaTime;
    if (m_RunningTime >= m_UpdateTime)
    {
        m_RunningTime = 0.0f;
        m_Animate += 25;
        ++m_Frame;
        if (m_Frame > m_MaxFrame) 
        { 
            m_Animate = 0;
            m_Frame = 0;
        }
    }

    // CHANGES ANIMATION STATE
    m_AnimState = m_AnimationStates[0];

    // SWITCH ANIMATATION STATES
    // switch (m_PlayerState)
    // {
    //     case PlayerAnimState::IDLE: m_MoveDown = 0; m_MaxFrame = 4; break;
    //     case PlayerAnimState::WALKING: m_MoveDown = 1; m_MaxFrame = 4; break;
    //     case PlayerAnimState::JUMPING: m_MoveDown = 2; m_MaxFrame = 0; break;
    //     case PlayerAnimState::START_DEATH: m_MoveDown = 3; m_MaxFrame = 4; break;
    //     case PlayerAnimState::MIDDLE_DEATH: m_MoveDown = 4; m_MaxFrame = 4; break;
    //     case PlayerAnimState::END_DEATH: m_MoveDown = 5; m_MaxFrame = 4; break;
    // }
}

void AnimationComponent::Draw() 
{
    Rectangle Source = Rectangle{m_Animate, (float)(16.7 * m_MoveDown), (float)(25 * m_Flip), 16.7}; // Rectangle Source = Rectangle{0, 0, m_Transform.size.x, m_Transform.size.y}; // x = 25, y = 16.5 (nth number of 4.25)
    Rectangle Destination = Rectangle{m_Transform->GetPosition().x, m_Transform->GetPosition().y, m_Transform->GetPosition().x, m_Transform->GetPosition().y};
    DrawTexturePro(m_RenderComponent->GetImageSpriteSheet(), Source, Destination, Vector2{0, 0}, 0, WHITE);
}
