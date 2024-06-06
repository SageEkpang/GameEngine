#include "CharacterComponent.h"

CharacterComponent::CharacterComponent() 
{
    m_Name = " ";

    m_Health = 0;
    m_Damage = 0;
    m_Speed = 0;

    m_MaxJumps = 2;
    m_CanJump = true;
}

void CharacterComponent::Update(float DeltaTime) 
{


}

void CharacterComponent::Draw() 
{
}