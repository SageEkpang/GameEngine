#ifndef CHARACTER_COMPONENT_H
#define CHARACTER_COMPONENT_H

// CUSTOM INCLUDE(s)
#include "Component.h"

class CharacterComponent: public Component
{
private:

    // CHARACTER VARIABLE(s) (Base)
    const char* m_Name;

    // CHARACTER VARIABLE(s) (Health)
    float m_Health;
    float m_MaxHealth;
    float m_Damage;
    bool m_Dead;

    // CHARACTER VARIABLE(s) (Movement)
    float m_Speed;

    // CHARACTER VARIABLE(s) (Jumping)
    int m_MaxJumps;
    int m_JumpCount;
    bool m_IsJumping;
    bool m_CanJump;

public:

    // CLASS FUNCTION(s)

    /// @brief Custom Character for Class (For Main Characters)
    CharacterComponent();

    /// @brief Default Destructor for Class
    ~CharacterComponent() {};



    // BASE FUNCTION(s)

    /// @brief Default Update function for Class 
    virtual void Update(float DeltaTime) override;

    /// @brief Default Draw function for Class
    virtual void Draw() override;



    // EXTRA FUNCTION(s)

    inline void GainHealth(float addHealth);
    inline void TakeDamage(float addDamage);
    
    inline void AddSpeed(float addSpeed) { m_Speed += addSpeed; } // NOT PLAYER SPEED, DOWNFORCE SPEED
    inline void AddToMaxJumps(int addJumps) { m_MaxJumps += addJumps; }



    // GETTER FUNCTION(s)

    inline const char* GetName() { return this->m_Name; }

    inline float GetHealth() { return this->m_Health; }
    inline float GetMaxHealth() { return this->m_MaxHealth; }
    inline float GetDamage() { return this->m_Damage; }
    inline float GetSpeed() { return this->m_Speed; }

    inline int GetMaxJumps() { return this->m_MaxJumps; }
    inline int GetJumpCount() { return this->m_JumpCount; }



    // SETTER FUNCTION(s)
    
    inline void SetName(const char* name) { this->m_Name = name; }

    inline void SetHealth(float health) { this->m_Health = health; }
    inline void SetMaxHealth(float maxHealth) { this->m_MaxHealth = maxHealth; }
    inline void SetDamage(float damage) { this->m_Damage = damage; }
    inline void SetSpeed(float speed) { this->m_Speed = speed; }

    inline void SetMaxJumps(int maxJumps) { this->m_MaxJumps = maxJumps; }
    inline void SetJumpCount(int jumpCount) { this->m_JumpCount = jumpCount; }
};

#endif