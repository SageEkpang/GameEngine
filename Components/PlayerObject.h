#ifndef PLAYER_H
#define PLAYER_H

// PARENT CLASS
#include "GameObject.h"

// COMPONENT(s)
#include "AnimationComponent.h"
#include "CharacterComponent.h"
#include "CollisionComponent.h"
#include "InputComponent.h"
#include "PhysicsComponent.h"
#include "RenderComponent.h"

class PlayerObject : public GameObject
{
private:

    CharacterComponent* m_Character;
    RenderComponent* m_Render;
    AnimationComponent* m_Animation;
    CollisionComponent* m_Collision;
    InputComponent* m_Input;
    PhysicsComponent* m_Physics;

public:

    // CLASS FUNCTION(s)

    /// @brief Default Constructor for Class
    /// @param tag 
    /// @param name 
    /// @param transform 
    /// @param health 
    /// @param damage 
    /// @param speed 
    /// @param maxJump 
    /// @param spriteSheet 
    PlayerObject(std::string tag, const char* name, Transform2Utility transform, float health, float maxHealth, float damage, float speed, float maxJump, const char* spriteSheet);

    /// @brief Default Destructor for Class
    ~PlayerObject();
    

    // BASE FUNCTION(s)

    /// @brief Default Update function for Class
    void Update(float DeltaTime) override;

    /// @brief Default Draw function for Class
    void Draw() override;

};

#endif