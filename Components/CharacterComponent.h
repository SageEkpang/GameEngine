#ifndef CHARACTER_COMPONENT_H
#define CHARACTER_COMPONENT_H

// CUSTOM INCLUDE(s)
#include "Component.h"

class CharacterComponent: public Component
{
private:

    // CHARACTER VARIABLE(s) (Base)
    std::string m_Name;

    // CHARACTER VARIABLE(s) (extra)
    float m_Health;
    float m_Damage;
    float m_Speed;

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

    inline void GainHealth(float addHealth) { m_Health += addHealth; }
    inline void TakeDamage(float addDamage) { m_Health -= addDamage; }
    
    inline void AddSpeed(float addSpeed) { m_Speed += addSpeed; } // NOT PLAYER SPEED, DOWNFORCE SPEED
    inline void AddToMaxJumps(int addJumps) { m_MaxJumps += addJumps; }



    // GETTER FUNCTION(s)

    inline float GetHealth() { return this->m_Health; }
    inline float GetDamage() { return this->m_Damage; }
    inline float GetSpeed() { return this->m_Speed; }

    inline int GetMaxJumps() { return this->m_MaxJumps; }
    inline int GetJumpCount() { return this->m_JumpCount; }


    // SETTER FUNCTION(s)
    
    inline void SetHealth(float health) { m_Health = health; }
    inline void SetDamage(float damage) { m_Damage = damage; }
    inline void SetSpeed(float speed) { m_Speed = speed; }

    inline void SetMaxJumps(int maxJumps) { m_MaxJumps = maxJumps; }
    inline void SetJumpCount(int jumpCount) { m_JumpCount = jumpCount; }
};

#endif