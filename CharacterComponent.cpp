#include "CharacterComponent.h"

CharacterComponent::CharacterComponent() 
{
    m_Name = " ";

    m_Health = 0;
    m_MaxHealth = 100;
    m_Damage = 0;
    m_Dead = false;

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

inline void CharacterComponent::GainHealth(float addHealth) 
{
    m_Health += addHealth;
    if (m_Health > m_MaxHealth) { m_Health = m_MaxHealth; }
}

inline void CharacterComponent::TakeDamage(float addDamage) 
{
    m_Health -= addDamage;
    if (m_Health <= 0) { m_Health = 0; m_Dead = true;}
}